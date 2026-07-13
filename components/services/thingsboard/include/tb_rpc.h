// Manejo de RPC de ThingsBoard: v1/devices/me/rpc/request/+
//
// Convención de nombres de método: verbo_sustantivo en snake_case
// (ej: "set_mode", "trigger_alarm"). Ver docs/thingsboard_integration.md.

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// `params_json` es el objeto "params" del request de ThingsBoard (puede
// ser NULL si el método no lleva parámetros). El handler retorna un JSON
// de respuesta (heap-allocado, tb_rpc lo libera tras publicarlo) o NULL
// si el método no requiere respuesta.
typedef char *(*tb_rpc_handler_t)(const char *params_json);

// Registra un handler para un método RPC. Máximo
// CONFIG_THINGSBOARD_RPC_MAX_HANDLERS métodos simultáneos.
esp_err_t tb_rpc_register_handler(const char *method, tb_rpc_handler_t handler);

esp_err_t tb_rpc_unregister_handler(const char *method);

#ifdef __cplusplus
}
#endif
