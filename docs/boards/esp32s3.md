# ESP32-S3

Notas específicas para el target `esp32s3` (dual-core Xtensa LX7, sin BT
clásico, BLE sí).

- Muchas devkits S3 usadas en los TPs traen PSRAM octal — confirmar en la
  placa entregada antes de asumir `CONFIG_SPIRAM_MODE_OCT` en
  `sdkconfig.defaults.esp32s3`.
- USB-OTG nativo (util para JTAG/consola sin conversor externo, según la
  devkit). Pedir video al profe para configurarlo !!!!! 
- Target sugerido para TPs con más periféricos simultáneos (varios buses
  I2C/UART/CAN a la vez) por tener más pines libres que el ESP32 clásico.

Completar acá el pinout específico del hardware entregado para cada TP.
