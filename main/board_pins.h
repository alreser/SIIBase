//ARCHIVO ÚNICO DEL PROYECTO DONDE SE TIENE TODA LA CONFIGURACIÓN DE PINES FÍSICOS UTILIZADOS DE LA PLACA
// Fuente única de verdad del cableado físico de ESTE proyecto/hardware.
// Si el TP cambia de placa o de wiring, se toca solo este archivo.

#pragma once
#include "driver/gpio.h"

// --- Relés ---
//#define PIN_RELAY_PUERTA      GPIO_NUM_22
//#define PIN_RELAY_ALARMA      GPIO_NUM_13


// ---- PWM  output ---- 
//#define PIN_PWM_TRANSISTOR     GPIO_NUM_18

// ---- Analog Output ----



// --- Sensores ---
//#define PIN_DS18B20_TEMP      GPIO_NUM_4

// --- LED de estado ---
#define PIN_LED_STATUS        GPIO_NUM_23