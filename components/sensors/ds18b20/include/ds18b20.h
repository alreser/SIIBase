// Componente de REFERENCIA para mostrar cómo estructurar un sensor con
// API directa (sin interfaz genérica): init + una función de lectura con
// el nombre que tenga sentido para el sensor (acá get_temperature).
// No incluye la implementación del protocolo 1-Wire ni del algoritmo de
// conversión de temperatura: eso es trabajo de cada equipo (o se resuelve
// con un componente de terceros vía idf_component.yml si la cátedra lo
// permite).
//
// Usar esta carpeta como plantilla para agregar sensores nuevos: copiar
// la estructura (CMakeLists.txt + include/<sensor>.h + <sensor>.c),
// renombrar funciones y completar.

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Inicializa el bus 1-Wire en el GPIO indicado.
esp_err_t ds18b20_init(int gpio_num);

// Dispara una conversión y devuelve la temperatura en °C.
esp_err_t ds18b20_get_temperature(float *out_celsius);

esp_err_t ds18b20_deinit(void);

#ifdef __cplusplus
}
#endif
