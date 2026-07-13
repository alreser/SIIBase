// Punto de entrada de la aplicación.
//
// Orden de arranque recomendado (ver docs/architecture.md):
//   1. storage_init()                         -> NVS listo
//   2. wifi_connect(ssid, password, retries)   -> bloquea hasta conectar
//   3. tb_client_start(&cfg)                   -> conecta MQTT a ThingsBoard
//   4. tb_attributes_subscribe(cb) / tb_rpc_register_handler(...)
//   5. Inicializar sensores/actuadores del TP (components/sensors/*,
//      components/actuators/*)
//   6. Crear las tasks propias de la lógica de aplicación del TP,
//      respetando las prioridades de common/task_priorities.h
//
// No hay event bus: cada servicio expone su estado con una función
// simple (wifi_is_connected(), tb_client_is_connected()) que se puede
// consultar desde cualquier task. Los callbacks de attributes/RPC se
// registran directo contra el servicio de ThingsBoard.
//
// TODO: completar con la lógica específica de cada proyecto. Este archivo
// es el único lugar donde "se conectan" todos los servicios con el código
// propio del TP.



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "led_status.h"

static const char *TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "SII2026 - Plantilla base");

    esp_err_t err = led_status_init(CONFIG_APP_STATUS_LED_GPIO);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error inicializando LED de estado: %s", esp_err_to_name(err));
        return;
    }


    while (1)
    {
        /* code */

        err = led_status_set(true);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error encendiendo LED de estado: %s", esp_err_to_name(err));
            return;
        }
        
         vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
    




    // TODO: storage_init();
    // TODO: wifi_connect(CONFIG_APP_WIFI_SSID, ..., CONFIG_APP_WIFI_MAXIMUM_RETRY);
    // TODO: tb_client_start(&cfg);
    // TODO: tb_attributes_subscribe(on_attributes_updated);
    // TODO: tb_rpc_register_handler("set_mode", on_set_mode);
    // TODO: inicializar sensores/actuadores del TP;
    // TODO: crear tasks de la lógica de aplicación del TP;
}
