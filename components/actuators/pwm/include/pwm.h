// Componente de actuador: PWM de uso general sobre el periférico LEDC.
//
// El alumno define GPIO, frecuencia y resolución; el componente se
// encarga de reservar canal y timer de LEDC automáticamente (no hay que
// elegirlos desde afuera). Es la primitiva de bajo nivel del template:
// no asume ningún significado del duty más allá de "tanto por ciento de
// tiempo en alto" o "tantos microsegundos de pulso" — componentes de más
// alto nivel (servo, control de un driver de motor, etc.) se pueden
// construir arriba de este, traduciendo su propio dominio (grados, RPM)
// a duty/pulso.
//
// Casos de uso típicos:
//   - Servos: pwm_set_pulse_width_us() con freq_hz=50 (el servo
//     interpreta el ancho de pulso, no el % de duty — típicamente
//     500-2400us según el modelo, consultar el datasheet puntual).
//   - Control de potencia/velocidad hacia un driver de motor (L298N,
//     puente H, etc.): pwm_set_duty_percent(), el duty ES directamente
//     la señal de control.
//   - Dimming de LEDs, control de SSR por duty, etc.
//
// Gestión de recursos LEDC: este componente reparte canal/timer con un
// contador estático interno (ver pwm.c) — simple y suficiente para la
// cantidad de salidas PWM que suele haber en un TP (1-4). Limitación a
// tener en cuenta: el contador NO libera el canal al hacer
// pwm_deinit() (una vez asignado, queda tomado el resto de la
// ejecución). Para el patrón típico de este template — inicializar todo
// una vez al arrancar y no volver a crear/destruir instancias en
// runtime — no es un problema real.

#pragma once

#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    gpio_num_t gpio;
    uint32_t   freq_hz;      // frecuencia del PWM (50Hz típico para servos; cientos de Hz a decenas de kHz para motores/dimming)
    uint8_t    resolution;    // bits de resolución del duty (ver SOC_LEDC_TIMER_BIT_WIDTH del target: 20 en ESP32 clásico, 14 en S3/P4)
} pwm_config_t;

typedef struct {
    ledc_channel_t channel;
    ledc_timer_t   timer;
    ledc_mode_t    speed_mode;
    uint32_t       freq_hz;
    uint32_t       max_duty;
    bool           initialized;
} pwm_t;

// Reserva un canal + timer de LEDC libres y arranca en 0% de duty.
// Retorna ESP_ERR_NO_MEM si no quedan canales/timers disponibles en el
// target (típicamente 6-8 canales y 4 timers, según el chip).
esp_err_t pwm_init(pwm_t *out, const pwm_config_t *config);

// Setea el duty directamente como porcentaje [0.0, 100.0]. Se satura
// (con warning) si el valor pedido queda fuera de rango.
esp_err_t pwm_set_duty_percent(pwm_t *out, float percent);

// Setea el duty a partir de un ancho de pulso en microsegundos, según la
// frecuencia configurada en pwm_init(). Pensado para servos: por
// ejemplo, con freq_hz=50 (período de 20000us), pulse_width_us=1500
// suele corresponder a la posición central — cada modelo de servo tiene
// su propio rango, consultar el datasheet.
// Se satura (con warning) si pulse_width_us supera el período (1e6/freq_hz).
esp_err_t pwm_set_pulse_width_us(pwm_t *out, uint32_t pulse_width_us);

esp_err_t pwm_deinit(pwm_t *out);

#ifdef __cplusplus
}
#endif
