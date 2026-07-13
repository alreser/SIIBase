// Macros comunes de verificación de errores, consistentes en todos los
// componentes de components/services/ y en los sensores/actuadores del proyecto.

#pragma once

#include "esp_err.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

// Loguea y retorna el error si `expr` no es ESP_OK. Uso:
//   APP_RETURN_ON_ERROR(tag, some_func(), "no se pudo inicializar X");
#define APP_RETURN_ON_ERROR(tag, expr, msg)                              \
    do {                                                                 \
        esp_err_t _err = (expr);                                         \
        if (_err != ESP_OK) {                                            \
            ESP_LOGE(tag, "%s (%s)", msg, esp_err_to_name(_err));         \
            return _err;                                                 \
        }                                                                \
    } while (0)

// Igual que arriba pero para funciones void: solo loguea, no retorna valor.
#define APP_LOG_ON_ERROR(tag, expr, msg)                                 \
    do {                                                                 \
        esp_err_t _err = (expr);                                         \
        if (_err != ESP_OK) {                                            \
            ESP_LOGE(tag, "%s (%s)", msg, esp_err_to_name(_err));         \
        }                                                                \
    } while (0)

#ifdef __cplusplus
}
#endif
