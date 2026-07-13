// Servicio de conexión WiFi en modo estación (STA).
//
// API simple e intencionalmente bloqueante: `wifi_connect()` no retorna
// hasta que hay IP asignada o se agotan los reintentos. Esto evita tener
// que introducir un event loop o callbacks para saber cuándo la red está
// lista — simplemente se llama antes de arrancar el resto de los
// servicios (thingsboard, etc.) en main/app_main.c.
//
// Si tu TP necesita reaccionar a una desconexión en runtime (por ejemplo,
// para pausar el envío de telemetría), consultá wifi_is_connected() desde
// tu propia task en vez de depender de un callback.

#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Conecta a la red indicada. Bloquea hasta conectar o hasta agotar
// `max_retries` intentos. Devuelve ESP_OK si quedó conectado.
esp_err_t wifi_connect(const char *ssid, const char *password, int max_retries);

bool wifi_is_connected(void);

esp_err_t wifi_disconnect(void);

#ifdef __cplusplus
}
#endif
