# SII2026 ESP32 Project Template

Plantilla base de proyecto **ESP-IDF** para los Trabajos Prácticos de Sistemas
Informáticos Industriales. Provee la **estructura de carpetas y el
contrato de funciones** para la infraestructura común (WiFi, cliente MQTT
para ThingsBoard, almacenamiento en NVS, convención de tareas FreeRTOS y
la forma de organizar sensores/actuadores), para que cada grupo se enfoque
en la **lógica específica de su problema de ingeniería**.

> **Este repo es un esqueleto de referencia, no una implementación
> resuelta.** Los archivos `.h` definen la firma de cada función (qué
> expone cada servicio/componente); los `.c` correspondientes están
> vacíos con comentarios `TODO` indicando qué hay que implementar. La idea
> es que cada equipo complete la infraestructura común una única vez y la
> reutilice en todos sus TPs.

Compatible con **ESP32, ESP32-S3 y ESP32-P4** (y en general cualquier target
soportado por ESP-IDF >= 5.x).

## Cómo usar este template

1. **No hagas fork.** Usá el botón "Use this template" de GitHub para
   crear tu propio repositorio `SII2026<NombreDeTuProyecto>`.
2. Cloná tu nuevo repo:
   ```bash
   git clone https://github.com/<tu-usuario>/SII2026<TuProyecto>.git
   cd SII2026<TuProyecto>
   ```
3. Configurá el target de tu placa:
   ```bash
   idf.py set-target esp32s3      # o esp32 / esp32p4
   ```
4. Copiá las credenciales de ejemplo y completá las tuyas:
   ```bash
   cp main/secrets.h.example main/secrets.h
   ```
   (`secrets.h` está en `.gitignore`, nunca subas credenciales reales)
5. Completá los `TODO` de `components/services/wifi`,
   `components/services/thingsboard` y `components/services/storage`.
6. Configurá vía menuconfig los parámetros del proyecto:
   ```bash
   idf.py menuconfig
   ```
7. Compilá y flasheá:
   ```bash
   idf.py build flash monitor
   ```
8. Seguí el checklist en [`docs/new_project_checklist.md`](docs/new_project_checklist.md)
   para adaptar el template a tu problema de ingeniería específico.

## Estructura del proyecto

```
SIIBase/
├── main/                       # Punto de entrada, app_main(), configuración del proyecto
├── components/
│   ├── common/                 # Macros de error + convención de prioridades de tasks
│   ├── services/
│   │   ├── wifi/               # Conexión WiFi STA (API directa, bloqueante)
│   │   ├── thingsboard/        # Cliente MQTT: telemetry, attributes, RPC
│   │   ├── storage/            # Wrapper de NVS (config persistente + buffer de sesiones)
│   │   ├── provisioning/       # Reservado (no implementado)
│   │   └── ota/                # Reservado (no implementado)
│   ├── sensors/                # Un componente por sensor, API directa (init + get_x)
│   │   └── ds18b20/             # Ejemplo de referencia (sensor de temperatura 1-Wire)
│   └── actuators/               # Un componente por actuador, API directa (init + set)
│       └── led_status/         # Ejemplo de referencia (LED de estado)
├── docs/                       # Decisiones de arquitectura y guías
└── .github/workflows/          # CI: build matrix para esp32/esp32s3/esp32p4
```

Ver el detalle de cada capa y las decisiones de diseño en
[`docs/architecture.md`](docs/architecture.md).

## Principios de diseño

- **Un componente, una responsabilidad.** Cada sensor/actuador es un
  componente ESP-IDF independiente con **funciones directas** (sin
  interfaz genérica): `<sensor>_init()`, `<sensor>_get_x()`,
  `<actuador>_set()`. Agregar un sensor nuevo no debería tocar código de
  otros sensores.
- **`services/*` es infraestructura, no lógica de negocio.** WiFi, MQTT y
  NVS viven en `components/services/*` y no conocen nada del problema de
  ingeniería particular. La lógica de tu TP (máquina de estados, reglas de
  alarma, etc.) vive en `main/` o en un componente propio de tu proyecto.
- **Sin event bus.** Los componentes se llaman directamente entre sí. El
  estado de conexión se consulta con funciones simples
  (`wifi_is_connected()`, `tb_client_is_connected()`) en vez de
  suscribirse a eventos. Ver `docs/architecture.md` para el detalle de
  esta decisión.
- **Tasks libres, convención de prioridades fija.** Cada equipo diseña su
  propia máquina de estados con tasks + colas de FreeRTOS. 
- **MQTT como único transporte hacia ThingsBoard**, con la convención de
  tópicos estándar de ThingsBoard (`v1/devices/me/telemetry`,
  `v1/devices/me/attributes`, `v1/devices/me/rpc/...`). Ver
  [`docs/thingsboard_integration.md`](docs/thingsboard_integration.md).


