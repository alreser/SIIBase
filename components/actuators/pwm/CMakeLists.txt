idf_component_register(SRCS "pwm.c"
                    INCLUDE_DIRS "include"
                    REQUIRES freertos esp_driver_ledc esp_driver_gpio)
