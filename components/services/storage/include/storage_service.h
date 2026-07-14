// Wrapper de NVS con dos responsabilidades:
//
//  1. Config persistente simple (clave/valor) para atributos recibidos de
//     ThingsBoard que deben sobrevivir a un reinicio (umbrales, modo de
//     operación, etc.)
//
//  2. Buffer circular de "sesiones" para el patrón store & forward que
//     necesitan los TPs con conectividad intermitente: cada sesión es un
//     blob JSON que se guarda en NVS cuando no hay red y se envía cuando
//     la conexión vuelve.
//
// El tamaño y cantidad de sesiones bufferizadas depende de la partición
// "storage" definida en partitions.csv o el que hayan seleccionado para su proyecto.

#pragma once

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t storage_init(void);

// --- Config persistente (clave/valor simple) ---

//TODO: acá deben dejar o ampliar a con los tipos de claves que vayan a necesitar en cada proyecto
/// los que no implementen conviene borrarlos. 
esp_err_t storage_set_config_str(const char *key, const char *value);
esp_err_t storage_get_config_str(const char *key, char *out_buf, size_t out_buf_len);

esp_err_t storage_set_config_f32(const char *key, float value);
esp_err_t storage_get_config_f32(const char *key, float *out_value);

esp_err_t storage_set_config_i32(const char *key, int32_t value);
esp_err_t storage_get_config_i32(const char *key, int32_t *out_value);

// --- Buffer de sesiones (store & forward) ---

// En teoría es sólo para el grupo de TallTrack
#define STORAGE_MAX_SESSIONS 30  // ver docs/architecture.md, ajustar según partición NVS

// Encola una sesión (JSON) pendiente de sincronizar. Si el buffer está
// lleno, sobrescribe la sesión más antigua.
esp_err_t storage_session_enqueue(const char *json);

// Recorre las sesiones no sincronizadas. `cb` retorna true si la sesión se
// publicó con éxito (se marca como enviada) o false si falló (queda
// pendiente para el próximo intento). El recorrido se corta ante el
// primer fallo para no reordenar sesiones.
typedef bool (*storage_session_cb_t)(const char *json, void *ctx);
esp_err_t storage_session_drain(storage_session_cb_t cb, void *ctx);

uint32_t storage_session_pending_count(void);

#ifdef __cplusplus
}
#endif
