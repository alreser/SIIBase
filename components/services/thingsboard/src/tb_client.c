// Implementación de tb_client.h
//
// Acá va: creación del cliente esp-mqtt (esp_mqtt_client_init/start),
// registro del handler de eventos MQTT (CONNECTED/DISCONNECTED/DATA), y
// despacho de MQTT_EVENT_DATA hacia tb_attributes y tb_rpc (ver
// tb_internal.h). Sin event bus propio: tb_client_is_connected() alcanza
// para que el resto de la app sepa el estado de la conexión.
//
// TODO: implementar tb_client_start(), tb_client_is_connected(),
//       tb_client_publish(), tb_client_stop()

#include "tb_client.h"
#include "tb_internal.h"
