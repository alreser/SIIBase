# Checklist: crear un proyecto nuevo a partir del template

- [ ] Crear repo desde "Use this template" en GitHub, nombrarlo
      `SII2026<NombreProyecto>`.
- [ ] `idf.py set-target <esp32|esp32s3|esp32p4>`.
- [ ] Actualizar `CMakeLists.txt` (nombre del proyecto) y este README con
      el nombre real del TP y el grupo.
- [ ] `cp main/secrets.h.example main/secrets.h` y completar WiFi +
      ThingsBoard access token.
- [ ] `.github/workflows/build.yml` una vez creado el proyecto específico del TP, 
      configurar sólo la placa que  se utilizará y verificar que funciona el CI en github Actions.
- [ ] Completar la implementación de `components/services/wifi`,
      `components/services/thingsboard` y `components/services/storage`
      (son esqueletos con `TODO`, se implementan una única vez y se
      reutilizan en case todos los TPs).
- [ ] Definir en `main/Kconfig.projbuild` los pines GPIO específicos del
      hardware entregado (sensores/actuadores del TP).
- [ ] Por cada sensor/actuador del TP que no exista en
      `components/sensors/` o `components/actuators/`: crear un
      componente nuevo con API directa (copiar `ds18b20/` o `led_status/`
      como plantilla — `<nombre>_init()` + `<nombre>_get_x()` /
      `<nombre>_set()`).
- [ ] Definir las claves de telemetría, atributos y métodos RPC específicos
      del TP en `main/app_config.h` (ver
      `docs/thingsboard_integration.md`).
**OPCIONAL** 
- [ ] Implementar la máquina de estados / lógica de negocio del TP (en
      `main/` o en un componente propio `components/app_logic/`), llamando
      directamente a las funciones de `services/*` 

- [ ] Si el TP requiere store & forward (Flota 4G, Seguidor Solar,
      AutoLog): usar `storage_session_*` para el buffer de sesiones.
      
- [ ] Exportar el dashboard de ThingsBoard a
      `tools/thingsboard/dashboard_export.json` antes de la entrega.
- [ ] Actualizar el diagrama de conexiones y la lista de materiales en
      `docs/` (o en el README del proyecto específico).
- [ ] Verificar que el workflow de CI (`.github/workflows/build.yml`)
      compila para el target real de la placa entregada.
