// Componente de REFERENCIA más simple posible (un GPIO digital) para
// mostrar cómo estructurar un actuador con API directa (sin interfaz
// genérica). Usar como plantilla para relay/, servo_pwm/, buzzer/, etc.

#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t led_status_init(int gpio_num);

esp_err_t led_status_set(bool on);

esp_err_t led_status_deinit(void);

#ifdef __cplusplus
}
#endif
