// Componente de actuador: relé digital sobre un GPIO, con soporte para
// lógica inversa (módulos de relé que se activan con nivel bajo) 
//
// Uso típico:
//
//   relay_t relay_puerta = {0};
//   relay_init(&relay_puerta, &(relay_config_t){
//       .gpio_num = 26,
//       .active_low = true,   // el módulo de relé se energiza con nivel bajo
//   });
//   relay_set(&relay_puerta, true);   // "abrir" / "activar", en sentido lógico
//   ...
//   relay_deinit(&relay_puerta);

#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int  gpio_num;

    // true si el módulo de relé se activa con nivel BAJO en el GPIO
    // (muy común en módulos de relé baratos con optoacoplador, que traen
    // la entrada IN activa en low). false = lógica normal (activo en alto).
    bool active_low;

    // Estado inicial deseado apenas se inicializa el relé (antes de que
    // la lógica de la app decida qué hacer). Por defecto, false (apagado)
    // es lo más seguro para la mayoría de los casos (puertas cerradas,
    // motores detenidos, etc.) — pero es configurable porque no siempre
    // es así (por ejemplo, un relé normalmente cerrado que debe arrancar
    // "activado" para mantener un circuito cerrado por defecto).
    bool initial_state_on;
} relay_config_t;

typedef struct {
    int  gpio_num;
    bool active_low;
    bool state_on;   // último estado lógico aplicado (no el nivel físico del pin)
    bool initialized;
} relay_t;

// Configura el GPIO como salida y aplica `config->initial_state_on`.
// `relay` debe ser un struct provisto por el llamador (podés tener uno
// por cada relé físico) y vive mientras el relé esté en uso.
esp_err_t relay_init(relay_t *relay, const relay_config_t *config);

// Aplica el estado lógico indicado. `on` siempre se interpreta en sentido
// lógico ("activado"/"desactivado"), independientemente de `active_low`:
// quien llama a esta función no necesita pensar en niveles eléctricos.
esp_err_t relay_set(relay_t *relay, bool on);

// Invierte el estado actual. Atajo útil para pulsadores/toggle.
esp_err_t relay_toggle(relay_t *relay);

// Devuelve el último estado lógico aplicado (no vuelve a leer el pin).
bool relay_get(const relay_t *relay);

// Libera el GPIO (lo vuelve a la configuración por defecto de reset).
esp_err_t relay_deinit(relay_t *relay);

#ifdef __cplusplus
}
#endif
