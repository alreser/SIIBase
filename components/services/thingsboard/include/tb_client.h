// Cliente MQTT hacia ThingsBoard. Envuelve esp-mqtt y expone las tres
// primitivas de la "Basic MQTT API" de ThingsBoard: telemetry, attributes
// y RPC (ver tb_telemetry.h, tb_attributes.h, tb_rpc.h).
//
// Requiere que services/wifi ya esté conectado (wifi_connect() exitoso)
// antes de llamar a tb_client_start().
//
// No usa un event bus propio: la conexión/desconexión se puede consultar
// en cualquier momento con tb_client_is_connected(). Si tu lógica necesita
// reaccionar a la reconexión (por ejemplo, enviar el buffer de sesiones),
// consultá este flag desde tu propia task en vez de depender de un callback.

#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *mqtt_host;      // ej: "demo.thingsboard.io"
    int mqtt_port;              // ej: 8883 (TLS) u 1883 (sin TLS, no recomendado)
    const char *access_token;   // Access Token del dispositivo en ThingsBoard
    bool use_tls;
} tb_client_config_t;

// Conecta al broker MQTT. Se reconecta automáticamente ante caídas de red.
esp_err_t tb_client_start(const tb_client_config_t *config);

bool tb_client_is_connected(void);

// Usado internamente por tb_telemetry.c / tb_attributes.c / tb_rpc.c.
// No debería ser necesario llamarlo directamente desde la app.
esp_err_t tb_client_publish(const char *topic, const char *payload, int qos);

esp_err_t tb_client_stop(void);

#ifdef __cplusplus
}
#endif
