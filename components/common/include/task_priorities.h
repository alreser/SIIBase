// Convención de prioridades de tareas FreeRTOS, común a todos los TPs.
// No es un framework de máquina de estados: cada proyecto crea sus propias
// tasks con xTaskCreate() libremente, solo pedimos respetar esta escala de
// prioridades para que sensado/comunicación/seguridad no se pisen entre sí.
// Ver docs/architecture.md, sección "Convención de tasks y prioridades".

#pragma once

// Mayor número = mayor prioridad (igual que en FreeRTOS).
typedef enum {
    APP_TASK_PRIO_MAINTENANCE = 1,  // logging, housekeeping, tareas no críticas
    APP_TASK_PRIO_COMM        = 3,  // sincronización con WiFi/ThingsBoard
    APP_TASK_PRIO_LOGIC       = 4,  // máquina de estados / lógica de negocio del TP
    APP_TASK_PRIO_SENSING     = 5,  // lectura periódica de sensores
    APP_TASK_PRIO_SAFETY      = 10, // paro de emergencia, watchdogs críticos
} app_task_priority_t;
