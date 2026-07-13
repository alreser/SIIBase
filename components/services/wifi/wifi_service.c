// Implementación de wifi_service.h
//
// Acá va: inicialización de esp_netif + wifi driver en modo STA,
// registro de un handler interno para WIFI_EVENT/IP_EVENT que solo
// setea un flag/semáforo local (no hace falta un event bus propio de la
// app para esto: alcanza con una variable + un semáforo binario de
// FreeRTOS para desbloquear wifi_connect()), y reintentos hasta
// `max_retries`.
//
// TODO: implementar wifi_connect(), wifi_is_connected(), wifi_disconnect()

#include "wifi_service.h"
