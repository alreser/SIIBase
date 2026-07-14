// Implementación de storage_service.h
//
// Acá va: apertura de namespaces NVS ("app_config" para parámetros
// persistentes, "app_sessions" para el buffer circular de store &
// forward), y la lógica de almacenado/Enviado de sesiones.
// Ver docs/architecture.md para el diseño del buffer circular.
//
// TODO: implementar storage_init(), get/set de config (str/f32/i32),
//       storage_session_enqueue(), storage_session_drain(),
//       storage_session_pending_count()

#include "storage_service.h"
