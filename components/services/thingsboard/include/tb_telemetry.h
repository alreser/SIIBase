// Publicación de telemetría a v1/devices/me/telemetry.
// Ver docs/thingsboard_integration.md para la convención de payloads.

#pragma once

#include "esp_err.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Publica un JSON ya armado por el llamador, ej:
//   tb_telemetry_publish_json("{\"temperature\":23.5,\"state\":\"production\"}");
esp_err_t tb_telemetry_publish_json(const char *json);

// Helper para el caso más simple: una clave numérica.
esp_err_t tb_telemetry_publish_kv(const char *key, double value);

// Publica telemetría con timestamp explícito (para datos bufferizados que
// se envían fuera de tiempo real, ej. sesiones NVS guardadas sin conexión).
//   {"ts": 1717000000000, "values": {...}}
esp_err_t tb_telemetry_publish_with_ts(uint64_t ts_epoch_ms, const char *values_json);

#ifdef __cplusplus
}
#endif
