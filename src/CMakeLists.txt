# Configuración básica
cmake_minimum_required(VERSION 3.13)

# Importar el SDK 
include(pico_sdk_import.cmake)

# Nombre del proyecto
project(proximity-pico)

# Inicializar SDK
pico_sdk_init()

# -----------------------------------------------------------
# LISTA DE ARCHIVOS .C
# -----------------------------------------------------------
add_executable(proximity_pico
    src/app/main.c                    
    src/hal/hal_sensor.c           
    src/hal/hal_output.c           
    src/drivers/hcsr04/hcsr04.c    
    src/drivers/oled/ssd1306.c
)

target_include_directories(proximity_pico PRIVATE
    src
)

target_link_libraries(proximity_pico
    pico_stdlib
    hardware_pwm 
    hardware_i2c    
)

# Generar el archivo final (.uf2)
pico_add_extra_outputs(proximity_pico)
