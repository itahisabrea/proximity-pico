# 1. Configuración básica
cmake_minimum_required(VERSION 3.13)

# Importar el SDK 
include(pico_sdk_import.cmake)

# 2. Nombre de nuestro proyecto
project(sctr_project)

# Inicializar SDK
pico_sdk_init()

# 3. Crear el ejecutable
add_executable(sctr_app
    src/app/main.c
    src/drivers/hcsr04/hcsr04.c
    src/drivers/oled/ssd1306.c   # Compila el código de la pantalla
)

# 4. Decirle dónde están los archivos de cabecera (.h)
target_include_directories(sctr_app PRIVATE
    src/app
    src/hal
    src/drivers
    src/drivers/hcsr04
    src/drivers/oled             
)

# 5. Enlazar librerías estándar
target_link_libraries(sctr_app 
    pico_stdlib
    hardware_pwm  # Necesario para el buzzer
    hardware_i2c  # Necesario para la pantalla OLED (¡Ya lo tenías bien puesto!)
)

# 6. Generar el archivo .uf2 para la placa
pico_add_extra_outputs(sctr_app)
