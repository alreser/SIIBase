// Suscripción a "shared attributes" de ThingsBoard (parámetros de
// configuración que el operador setea desde el dashboard) y publicación de
// "client attributes" (estado del dispositivo).

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Callback invocado directamente cuando llega una actualización de
// atributos (se ejecuta en la task interna del cliente MQTT: si el
// procesamiento es largo, encolar el trabajo a tu propia task en vez de
// bloquear acá). `json` es el payload crudo con las claves actualizadas.
typedef void (*tb_attributes_cb_t)(const char *json);

// Se suscribe a v1/devices/me/attributes (shared attributes push) y a la
// respuesta de v1/devices/me/attributes/request/+ (attributes pull inicial).
esp_err_t tb_attributes_subscribe(tb_attributes_cb_t cb);

// Publica client-side attributes (información de estado/versión del
// dispositivo, no configuración).
esp_err_t tb_attributes_publish_json(const char *json);

// Pide explícitamente los shared attributes actuales (attributes request).
esp_err_t tb_attributes_request(const char *keys_csv);

#ifdef __cplusplus
}
#endif
