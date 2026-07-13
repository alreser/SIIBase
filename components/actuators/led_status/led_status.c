#include "led_status.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static int s_gpio_num = -1;
static bool s_is_initialized = false;

esp_err_t led_status_init(int gpio_num)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << gpio_num,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    esp_err_t err = gpio_config(&io_conf);
    if (err != ESP_OK) {
        return err;
    }

    s_gpio_num = gpio_num;
    s_is_initialized = true;

    return gpio_set_level(s_gpio_num, 0);
}

esp_err_t led_status_set(bool on)
{
    if (!s_is_initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    return gpio_set_level(s_gpio_num, on ? 1 : 0);
}

esp_err_t led_status_deinit(void)
{
    if (!s_is_initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = gpio_set_level(s_gpio_num, 0);
    esp_err_t reset_err = gpio_reset_pin(s_gpio_num);

    s_gpio_num = -1;
    s_is_initialized = false;

    return (err != ESP_OK) ? err : reset_err;
}
