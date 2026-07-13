# ESP32 (clásico)

Notas específicas para el target `esp32` (dual-core Xtensa LX6).

- Sin PSRAM en la mayoría de las devkits usadas en los TPs — evitar buffers
  grandes en heap sin verificar memoria disponible (`esp_get_free_heap_size()`).
- WiFi + BT clásico integrados.
- Usado como target de referencia/desarrollo cuando el TP no exige
  explícitamente S3 o P4.

Completar acá el pinout específico del hardware entregado para cada TP
(qué GPIO va a cada sensor/actuador), o documentarlo en el README del
proyecto derivado del template.
