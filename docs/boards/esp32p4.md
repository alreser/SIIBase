# ESP32-P4

Notas específicas para el target `esp32p4` (dual-core RISC-V de alto
rendimiento, pensado para procesamiento de video/IA local).

- **No tiene WiFi/BT propio.** La conectividad se resuelve con un
  ESP32-C6 co-procesado (típicamente vía SDIO/`esp_hosted`), según la
  devkit entregada — revisar el manual de la placa específica.
- Pensado para TPs con visión artificial/reconocimiento de gestos
  (esp-dl / esp-who), que quedan **fuera del alcance de este template**:
  agregar esos componentes en el proyecto derivado, no en la base común.
- Requiere `CONFIG_SPIRAM=y` para los buffers de imagen/inferencia.

Completar acá el pinout específico del hardware entregado, incluyendo la
interfaz de cámara si el TP la usa.
