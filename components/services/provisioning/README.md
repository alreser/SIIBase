# services/provisioning/

Reservado para un futuro servicio de aprovisionamiento (WiFi provisioning
vía BLE/SoftAP, o provisioning de credenciales de ThingsBoard). No forma
parte del alcance actual del template — hoy las credenciales se configuran
por `menuconfig` / `main/secrets.h`.

Si tu TP lo necesita, este es el lugar donde agregar el componente
(`idf_component_register` con su propio `CMakeLists.txt`, siguiendo la
misma convención que `services/wifi` y `services/storage`).
