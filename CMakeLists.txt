cmake_minimum_required(VERSION 3.16)
#incluyo las subcarpetas dentro de /componentes/.... para que espidf las reconozca como pomponentes.
set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/components/sensors
    ${CMAKE_CURRENT_SOURCE_DIR}/components/actuators
    ${CMAKE_CURRENT_SOURCE_DIR}/components/services
    ${CMAKE_CURRENT_SOURCE_DIR}/components/common
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Renombrar al nombre real del proyecto/TP al crear el repo desde el template.
project(sii2026_esp32_template)
