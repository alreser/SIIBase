idf_component_register(SRCS "relay.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos esp_driver_gpio)