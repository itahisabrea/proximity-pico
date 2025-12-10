/*
 * Archivo: hal_output.c
 * Descripción: Implementación del control de luces, sonido y pantalla.
 * Responsables: Josechu y Pablo
 */

#include "hal/hal_output.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// TODO: Cuando tengamos la librería de la pantalla, descomentad esta línea:
// #include "drivers/oled/NOMBRELIBRERIA"

void HAL_output_init(void) {
    // --- 1. CONFIGURACIÓN DE LEDS Y BUZZER ---
    const uint pins_salida[] = {PIN_LED_RED, PIN_LED_AMBER, PIN_LED_GREEN, PIN_BUZZER};
    
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_salida[i]);
        gpio_set_dir(pins_salida[i], GPIO_OUT);
        gpio_put(pins_salida[i], 0); // Empezamos con todo apagado
    }

    // --- 2. CONFIGURACIÓN DE LA PANTALLA ---
    /* * TAREA JOSECHU/PABLO: 
     * Aquí tenemos que inicializar el I2C y la pantalla.
     * Seguramente necesitemos algo parecido a esto:
     */
    
    // i2c_init(I2C_PORT, 400 * 1000);
    // gpio_set_function(PIN_I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(PIN_I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(PIN_I2C_SDA);
    // gpio_pull_up(PIN_I2C_SCL);
    
    // NOMBRELIBRERIA_init(); // <--- Llamada a la libreria
}

void HAL_set_system_state(SystemState_t state) {
    // Apagamos todo para asegurar un estado limpio
    gpio_put(PIN_LED_RED, 0);
    gpio_put(PIN_LED_AMBER, 0);
    gpio_put(PIN_LED_GREEN, 0);
    gpio_put(PIN_BUZZER, 0);

/* * TAREA JOSECHU/PABLO: 
     * Rellenad el switch para encender lo que toque en cada caso.
   

    switch (state) {
        case STATE_GREEN:
            // TODO: Encender LED Verde
            // TODO: Escribir "SEGURO o DISTANCIA SEGURA o lo que querais" en la pantallita
            break;

        case STATE_AMBER:
            // TODO: Encender LED Ámbar
            // TODO: Hacer sonar el Buzzer bajito (opcional, esto hay que decidir que vamos a hacer)
            // TODO: Escribir "PRECAUCION o CUIDADO" en la pantallita
            break;

        case STATE_RED:
            // TODO: Encender LED Rojo
            // TODO: Encender Buzzer a todo volumen ajajaj
            // TODO: Escribir "STOP!! o PELIGRO" en la pantallita
            break;
    }
}
