// Declaraciones compartidas SOLO entre los .c de services/thingsboard.
// No se instala en include/ a propósito: es detalle de implementación.

#pragma once

#include "mqtt_client.h"

esp_mqtt_client_handle_t tb_client__get_handle(void);

void tb_attributes__on_mqtt_connected(void);
void tb_attributes__on_mqtt_data(esp_mqtt_event_handle_t event);

void tb_rpc__on_mqtt_connected(void);
void tb_rpc__on_mqtt_data(esp_mqtt_event_handle_t event);
