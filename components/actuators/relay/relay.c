#include "relay.h"

#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "relay";

// Traduce estado lógico -> nivel físico del pin, según active_low.
static inline uint32_t logical_to_level(const relay_t *relay, bool on)
{
    return relay->active_low ? (on ? 0 : 1) : (on ? 1 : 0);
}

esp_err_t relay_init(relay_t *relay, const relay_config_t *config)
{
    if (relay == NULL || config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (config->gpio_num < 0 || !GPIO_IS_VALID_OUTPUT_GPIO(config->gpio_num)) {
        ESP_LOGE(TAG, "GPIO %d no es un pin de salida válido", config->gpio_num);
        return ESP_ERR_INVALID_ARG;
    }

    relay->gpio_num  = config->gpio_num;
    relay->active_low = config->active_low;
    relay->state_on   = config->initial_state_on;
    relay->initialized = false;

    // Nota: gpio_reset_pin() deja el pin en modo input de alta impedancia
    // por un instante antes de configurarlo como salida. Para relés donde
    // ese estado transitorio importa (por ejemplo, si el módulo de relé
    // no tiene su propia resistencia de pull en la entrada IN), agregar
    // una resistencia de pull-up/pull-down externa acorde a active_low.
    gpio_reset_pin(relay->gpio_num);

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << relay->gpio_num,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "gpio_config falló en GPIO %d (%s)", relay->gpio_num, esp_err_to_name(err));
        return err;
    }

    // Aplica el estado inicial apenas se configura la salida, para
    // minimizar el tiempo en que el relé queda en un estado indefinido.
    err = gpio_set_level(relay->gpio_num, logical_to_level(relay, relay->state_on));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "No se pudo aplicar el estado inicial en GPIO %d (%s)", relay->gpio_num, esp_err_to_name(err));
        return err;
    }

    relay->initialized = true;
    ESP_LOGI(TAG, "Relay en GPIO %d listo (active_low=%d, estado inicial=%s)",
             relay->gpio_num, relay->active_low, relay->state_on ? "ON" : "OFF");
    return ESP_OK;
}

esp_err_t relay_set(relay_t *relay, bool on)
{
    if (relay == NULL || !relay->initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = gpio_set_level(relay->gpio_num, logical_to_level(relay, on));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "No se pudo setear GPIO %d (%s)", relay->gpio_num, esp_err_to_name(err));
        return err;
    }

    relay->state_on = on;
    return ESP_OK;
}

esp_err_t relay_toggle(relay_t *relay)
{
    if (relay == NULL || !relay->initialized) {
        return ESP_ERR_INVALID_STATE;
    }
    return relay_set(relay, !relay->state_on);
}

bool relay_get(const relay_t *relay)
{
    return (relay != NULL) && relay->state_on;
}

esp_err_t relay_deinit(relay_t *relay)
{
    if (relay == NULL || !relay->initialized) {
        return ESP_ERR_INVALID_STATE;
    }
    gpio_reset_pin(relay->gpio_num);
    relay->initialized = false;
    return ESP_OK;
}
