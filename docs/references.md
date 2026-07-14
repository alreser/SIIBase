# Referencias a la documentación técnica de las placas

Les dejo el punto de partida de la documentación sobre el toolchain de **espressif**

Documentación oficial recomendada para trabajar con este template..

## ESP-IDF (Espressif)

- **Programming Guide (general, ESP32):**

  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/
  Reemplazar `esp32` por `esp32s3` o `esp32p4` en la URL para ver la guía
  específica de esa placa (algunos periféricos y ejemplos difieren).

- **Get Started (instalación de toolchain, primer proyecto):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html
- **API Reference — GPIO:**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
- **API Reference — Wi-Fi:**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html
- **API Reference — NVS (Non-Volatile Storage), usado en `services/storage`:**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html
- **API Reference — Partition Tables (para editar `partitions.csv`):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/partition-tables.html
- **API Reference — FreeRTOS (tasks, colas, semáforos):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
- **Kconfig (cómo se arman los menús de `menuconfig`, útil para editar
  `Kconfig.projbuild`):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/kconfig.html
- **Error Handling (convenciones `esp_err_t`, usadas en `common/error_utils.h`):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/error-handling.html
- **Deep Sleep (relevante para Seguidor Solar / AutoLog):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html

## MQTT (usado en `services/thingsboard`)

- **ESP-MQTT (cliente MQTT de Espressif):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/mqtt.html
- **Repositorio del componente (ejemplos de conexión TLS, mutual auth, etc.):**
  https://github.com/espressif/esp-mqtt

## ESP Component Registry (componentes de terceros/Espressif listos para usar)

- **Buscador de componentes:**
  https://components.espressif.com/
  Antes de escribir un driver desde cero (por ejemplo, para un sensor
  I2C específico), buscar acá — puede que ya exista un componente
  publicado y probado.
- **Cómo agregar una dependencia a un proyecto (`idf.py add-dependency`,
  `idf_component.yml`):**
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-component-manager.html

## ThingsBoard

- **MQTT Device API Reference (telemetry, attributes, RPC — la base de
  `services/thingsboard`):**
  https://thingsboard.io/docs/reference/mqtt-api/
- **Getting Started (conceptos generales de la plataforma: dispositivos,
  dashboards, device profiles):**
  https://thingsboard.io/docs/getting-started-guides/what-is-thingsboard/
- **API general (REST, Websocket, MQTT, Gateway — panorama completo):**
  https://thingsboard.io/docs/api/

## Referencia rápida de comandos ESP-IDF

| Comando                        | Qué hace                                             |
|---------------------------------|-------------------------------------------------------|
| `idf.py set-target esp32s3`     | Configura el target de compilación                    |
| `idf.py menuconfig`             | Abre el menú de configuración (Kconfig)                |
| `idf.py build`                  | Compila el proyecto                                    |
| `idf.py -p <puerto> flash`      | Flashea el firmware a la placa                          |
| `idf.py monitor`                | Abre el monitor serie (Ctrl+] para salir)               |
| `idf.py fullclean`              | Limpia el build completo (usar tras tocar CMakeLists.txt raíz) |
| `idf.py erase-flash`            | Borra toda la flash, incluida la NVS                     |


