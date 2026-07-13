# Integración con ThingsBoard (MQTT)

El template usa **exclusivamente MQTT** contra ThingsBoard, con las
convenciones estándar de tópicos ("Basic MQTT API"). No se usa HTTP ni CoAP.

## Autenticación

Cada dispositivo se autentica con **Access Token** (MQTT username = token,
sin password), configurado vía `menuconfig` o en `main/secrets.h`
(no versionado). Para escenarios que lo requieran (AutoLog, Flota 4G) se
puede migrar a X.509 más adelante; el cliente MQTT (`services/thingsboard`)
está aislado del mecanismo de auth para no romper el resto del código si
eso cambia.

## Telemetría

- Tópico: `v1/devices/me/telemetry`
- Payload: JSON plano `{"clave": valor, ...}` o con timestamp explícito
  `{"ts": 1717000000000, "values": {"clave": valor}}` para telemetría
  bufferizada (sesiones NVS enviadas fuera de tiempo, como en AutoLog).
- API: `tb_telemetry_publish_json(const char *json)` y helper
  `tb_telemetry_publish_kv(const char *key, double value)` para el caso
  simple.

## Atributos (parámetros de configuración remota)

- Suscripción a cambios: `v1/devices/me/attributes` (para "shared
  attributes" push) y request/response para "client-side attributes".
- Cada proyecto define su propio set de claves (ej:
  `temp_umbral_max`, `modo_operacion`, `geocerca_radio_m`) en
  `main/app_config.h` como constantes de nombre de atributo, y registra un
  callback en `tb_attributes_subscribe(const char *keys[], size_t n, cb)`.
- Los atributos recibidos se persisten en NVS vía `services/storage` para
  sobrevivir a un reinicio (ver `storage_set_config_str` / `_f32` / `_i32`).

## RPC (comandos)

- Tópico: `v1/devices/me/rpc/request/+`
- API: `tb_rpc_register_handler(const char *method, tb_rpc_cb_t cb)`.
- Convención de nombres de método: `verbo_sustantivo` en snake_case, por
  ejemplo `set_mode`, `trigger_alarm`, `reset_session_buffer`.
- La respuesta (si el método la requiere) se publica en
  `v1/devices/me/rpc/response/{request_id}` — lo maneja `services/thingsboard`
  automáticamente, el handler del proyecto solo devuelve el JSON de
  respuesta o `NULL` si no aplica.

## Manejo de desconexión (store & forward)

Para TPs con conectividad intermitente (Flota 4G, Seguidor Solar, AutoLog):

1. La lógica de aplicación intenta publicar vía `tb_telemetry_publish_*`.
2. Si `services/thingsboard` detecta que no hay conexión, en vez de perder el
   dato, se debe encolar la telemetría en `services/storage` (buffer
   circular en NVS) usando `storage_session_*` — ver
   `services/storage/include/storage_service.h`.
3. Al reconectar, `services/thingsboard` (o la task de sincronización del
   proyecto) recorre las sesiones pendientes y las publica con `ts`
   explícito, marcando cada una como `synced` solo tras `PUBACK` (QoS 1).

## Dashboards y provisioning

Los exports de dashboard de ThingsBoard (JSON) y los device profiles se
guardan en `tools/thingsboard/` para que quede versionado el estado del
tablero de cada entrega, no solo el firmware.
