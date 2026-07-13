// Implementación de tb_rpc.h
//
// Acá va: suscripción a v1/devices/me/rpc/request/+, parseo del JSON
// {"method": ..., "params": ...}, despacho al handler registrado según
// el nombre del método, y publicación de la respuesta (si corresponde)
// en v1/devices/me/rpc/response/{request_id}.
//
// TODO: implementar tb_rpc_register_handler(), tb_rpc_unregister_handler(),
//       y los hooks internos tb_rpc__on_mqtt_connected() /
//       tb_rpc__on_mqtt_data() (ver tb_internal.h)

#include "tb_rpc.h"
#include "tb_internal.h"
#include "tb_client.h"
