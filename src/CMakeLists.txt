# 1. Configuración básica
cmake_minimum_required(VERSION 3.13)

# Importar el SDK 
include(pico_sdk_import.cmake)

# 2. Nombre de nuestro proyecto (lo he puesto así temporalmente
project(sctr_project)

# Inicializar SDK
pico_sdk_init()

# 3. Crear el ejecutable
add_executable(sctr_app
    app/main.c
    # Aquí iremos añadiendo los archivos .c del HAL y Drivers más adelante
    # Por ejemplo:
    # hal/hal_sensor.c
    # drivers/hcsr04/hcsr04.c
)

# 4. Decirle dónde están los archivos de cabecera (.h)
target_include_directories(sctr_app PRIVATE
    app
    hal
    drivers
)

# 5. Enlazar librerías estándar
target_link_libraries(sctr_app 
    pico_stdlib
    hardware_pwm  # Necesario para el buzzer creo
    hardware_i2c  # Necesario para la pantalla OLED
)

# 6. Generar el archivo .uf2 para la placa
pico_add_extra_outputs(sctr_app)
