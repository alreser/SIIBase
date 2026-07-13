# tools/thingsboard/

Carpeta reservada para artefactos versionables relacionados a ThingsBoard
que no son firmware:

- `dashboard_export.json` — export del dashboard de ThingsBoard antes de
  cada entrega (Dashboard -> ... -> Export dashboard).
- `device_profile_export.json` — export del device profile, si el TP
  define uno custom (atributos, alarmas, etc.).
- Scripts propios de cada equipo para probar telemetría/RPC sin hardware
  (ej. un publisher MQTT de prueba), si lo necesitan.


