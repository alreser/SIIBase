# Arquitectura

## Capas

```
┌─────────────────────────────────────────────────────────────────┐
│  main/ (app_main.c)                                              │
│  - Llama en orden: storage_init() -> wifi_connect() ->           │
│    tb_client_start() -> tb_attributes_subscribe()/tb_rpc_...()   │
│  - Inicializa sensores/actuadores del TP                         │
│  - Crea las tasks de la app específica del TP                    │
└─────────────────────────────────────────────────────────────────┘
                │ llama directamente (sin event bus)
                ▼
┌───────────────────────────┐   ┌───────────────────────────────┐
│  Lógica de aplicación        │   │  components/sensors/*          │
│  (propia de cada TP)         │──►│  components/actuators/*        │
│  - Máquina de estados         │   │  API directa por componente:   │
│  - Reglas de alarma           │   │  <sensor>_init(), <sensor>_get_x()│
│  - Llama a tb_telemetry_*     │   └───────────────────────────────┘
│    cuando corresponde         │
└───────────────────────────┘
                │ llama directamente
                ▼
┌─────────────────────────────────────────────────────────────────┐
│  components/services/                                            │
│  ┌───────────┐  ┌───────────────┐  ┌───────────┐                  │
│  │ wifi      │  │ thingsboard    │  │ storage    │                  │
│  │ (STA +    │  │ (MQTT: tele-   │  │ (NVS:      │                  │
│  │ reconexión)│  │ metry/attrs/  │  │ config +   │                  │
│  │           │  │ RPC)           │  │ sesiones)  │                  │
│  └───────────┘  └───────────────┘  └───────────┘                  │
│  provisioning/ y ota/ quedan reservados para el futuro             │
└─────────────────────────────────────────────────────────────────┘
```


Esto hace que el código de `main/app_main.c` y de la lógica de aplicación
sea lineal y fácil de seguir con un debugger, a costa de un poco menos de
desacople formal — una mezcla razonable para el contexto de la cátedra.

## Convención de tasks y prioridades

Ver `components/common/include/task_priorities.h`. Resumen:

| Prioridad | Uso                                              |
|-----------|---------------------------------------------------|
| 10        | Seguridad / emergencia (paro de emergencia, watchdog de temperatura) |
| 5         | Sensado periódico                                  |
| 4         | Lógica de aplicación / máquina de estados          |
| 3         | Comunicación (WiFi/MQTT)                           |
| 1         | Tareas de mantenimiento (logging, housekeeping)    |

Esto evita que, por ejemplo, una publicación MQTT bloqueante retrase la
detección de una condición de emergencia.

## Multi-placa (ESP32 / ESP32-S3 / ESP32-P4)

El template no usa una capa de HAL propia: se apoya en `idf.py set-target`
y en `sdkconfig.defaults.<target>` para las diferencias de bajo nivel
(PSRAM, pines por defecto, etc.). Las diferencias de **pinout por
proyecto** (qué GPIO va a qué sensor) se configuran vía `menuconfig`
(`main/Kconfig.projbuild`), no hardcodeadas en el código.

Ver `docs/boards/` para las particularidades de cada placa usada en los TPs.

## opcionales del template


- **OTA / Provisioning.** Quedan como carpetas reservadas en
  `components/services/{ota,provisioning}/`, no implementadas. 
  pero pensadas por si las quiere agregar al proyecto. 
- **Librerías de IA/visión** (reconocimiento facial/gestos): fuera del
  alcance de este template, se documentan en `docs/boards/esp32p4.md`
  como extensión posible, no como núcleo del template.
