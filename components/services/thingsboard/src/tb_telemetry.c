// Implementación de tb_telemetry.h
//
// Acá va: armado del payload JSON de telemetría y publicación en
// v1/devices/me/telemetry vía tb_client_publish(). Ver
// docs/thingsboard_integration.md para la convención de payloads.
//
// TODO: implementar tb_telemetry_publish_json(), tb_telemetry_publish_kv(),
//       tb_telemetry_publish_with_ts()

#include "tb_telemetry.h"
#include "tb_client.h"
