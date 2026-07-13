// Implementación de ds18b20.h
//
// Acá va: inicialización del bus 1-Wire en el GPIO indicado, comando de
// conversión, lectura del scratchpad y cálculo de la temperatura.
// (Fuera del alcance de este template: es trabajo específico de cada
// equipo).
//
// TODO: implementar ds18b20_init(), ds18b20_get_temperature(), ds18b20_deinit()

#include "ds18b20.h"

esp_err_t ds18b20_init(int gpio_num)
{
    (void)gpio_num;
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t ds18b20_get_temperature(float *out_celsius)
{
    (void)out_celsius;
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t ds18b20_deinit(void)
{
    return ESP_ERR_NOT_SUPPORTED;
}
