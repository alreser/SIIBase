#include "pwm.h"
#include "soc/soc_caps.h"
#include "esp_log.h"

static const char *TAG = "pwm";

// Pool estático de canales/timers de LEDC del proyecto. Ver la nota de
// limitación en pwm.h (no se liberan al hacer pwm_deinit()).
static int s_next_channel = 0;
static int s_next_timer = 0;

// LEDC_LOW_SPEED_MODE existe en todos los targets (ESP32, S3, P4). El
// modo "high speed" solo existe en el ESP32 clásico — no lo usamos para
// que el componente sea portable sin cambios entre placas.
#define PWM_SPEED_MODE LEDC_LOW_SPEED_MODE

esp_err_t pwm_init(pwm_t *out, const pwm_config_t *config)
{
    if (out == NULL || config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (config->freq_hz == 0) {
        ESP_LOGE(TAG, "freq_hz debe ser > 0");
        return ESP_ERR_INVALID_ARG;
    }
    if (config->resolution == 0 || config->resolution > SOC_LEDC_TIMER_BIT_WIDTH) {
        ESP_LOGE(TAG, "resolution=%d fuera de rango (máximo del target: %d bits)",
                 config->resolution, SOC_LEDC_TIMER_BIT_WIDTH);
        return ESP_ERR_INVALID_ARG;
    }
    if (s_next_channel >= LEDC_CHANNEL_MAX) {
        ESP_LOGE(TAG, "No quedan canales LEDC libres (máximo %d)", LEDC_CHANNEL_MAX);
        return ESP_ERR_NO_MEM;
    }
    if (s_next_timer >= LEDC_TIMER_MAX) {
        ESP_LOGE(TAG, "No quedan timers LEDC libres (máximo %d)", LEDC_TIMER_MAX);
        return ESP_ERR_NO_MEM;
    }

    out->channel = (ledc_channel_t)s_next_channel;
    out->timer = (ledc_timer_t)s_next_timer;
    out->speed_mode = PWM_SPEED_MODE;
    out->freq_hz = config->freq_hz;
    out->max_duty = (1U << config->resolution) - 1;

    ledc_timer_config_t timer_cfg = {
        .speed_mode = out->speed_mode,
        .timer_num = out->timer,
        .duty_resolution = (ledc_timer_bit_t)config->resolution,
        .freq_hz = config->freq_hz,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    esp_err_t err = ledc_timer_config(&timer_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "ledc_timer_config falló (%s). ¿resolution + freq_hz son "
                       "combinación válida para el clock del target?", esp_err_to_name(err));
        return err;
    }

    ledc_channel_config_t channel_cfg = {
        .gpio_num = config->gpio,
        .speed_mode = out->speed_mode,
        .channel = out->channel,
        .timer_sel = out->timer,
        .duty = 0,      // arranca en 0%, no en un valor indefinido
        .hpoint = 0,
        .intr_type = LEDC_INTR_DISABLE,
    };
    err = ledc_channel_config(&channel_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "ledc_channel_config falló en GPIO %d (%s)", config->gpio, esp_err_to_name(err));
        return err;
    }

    s_next_channel++;
    s_next_timer++;
    out->initialized = true;

    ESP_LOGI(TAG, "pwm listo en GPIO %d: canal=%d timer=%d resolution=%d bits freq=%luHz",
             config->gpio, out->channel, out->timer, config->resolution, (unsigned long)config->freq_hz);
    return ESP_OK;
}

esp_err_t pwm_set_duty_percent(pwm_t *out, float percent)
{
    if (out == NULL || !out->initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    float clamped = percent;
    if (clamped < 0.0f) {
        ESP_LOGW(TAG, "percent=%.2f fuera de rango, se satura a 0%%", percent);
        clamped = 0.0f;
    } else if (clamped > 100.0f) {
        ESP_LOGW(TAG, "percent=%.2f fuera de rango, se satura a 100%%", percent);
        clamped = 100.0f;
    }

    uint32_t duty = (uint32_t)((clamped / 100.0f) * out->max_duty + 0.5f);
    if (duty > out->max_duty) {
        duty = out->max_duty;
    }

    esp_err_t err = ledc_set_duty(out->speed_mode, out->channel, duty);
    if (err != ESP_OK) {
        return err;
    }
    return ledc_update_duty(out->speed_mode, out->channel);
}

esp_err_t pwm_set_pulse_width_us(pwm_t *out, uint32_t pulse_width_us)
{
    if (out == NULL || !out->initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    uint32_t period_us = 1000000UL / out->freq_hz;
    uint32_t clamped = pulse_width_us;
    if (clamped > period_us) {
        ESP_LOGW(TAG, "pulse_width_us=%lu excede el período (%luus a %luHz), se satura",
                 (unsigned long)pulse_width_us, (unsigned long)period_us, (unsigned long)out->freq_hz);
        clamped = period_us;
    }

    uint32_t duty = (uint32_t)(((uint64_t)clamped * out->max_duty) / period_us);
    if (duty > out->max_duty) {
        duty = out->max_duty;
    }

    esp_err_t err = ledc_set_duty(out->speed_mode, out->channel, duty);
    if (err != ESP_OK) {
        return err;
    }
    return ledc_update_duty(out->speed_mode, out->channel);
}

esp_err_t pwm_deinit(pwm_t *out)
{
    if (out == NULL || !out->initialized) {
        return ESP_ERR_INVALID_STATE;
    }
    esp_err_t err = ledc_stop(out->speed_mode, out->channel, 0);
    out->initialized = false;
    return err;
}
