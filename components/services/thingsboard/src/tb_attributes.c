// Implementación de tb_attributes.h
//
// Acá va: suscripción a v1/devices/me/attributes (shared attributes push)
// y v1/devices/me/attributes/response/+ (respuesta a un request), parseo
// del JSON recibido y llamada directa al callback registrado por la app
// (sin pasar por ningún event bus).
//
// TODO: implementar tb_attributes_subscribe(), tb_attributes_publish_json(),
//       tb_attributes_request(), y los hooks internos
//       tb_attributes__on_mqtt_connected() / tb_attributes__on_mqtt_data()
//       (ver tb_internal.h)

#include "tb_attributes.h"
#include "tb_internal.h"
#include "tb_client.h"
