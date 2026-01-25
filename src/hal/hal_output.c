/*
 * Archivo: hal_output.c
 * Descripción: Implementación del control de luces, sonido y pantalla.
 * Responsables: Josechu y Pablo
 */

#include "hal/hal_output.h"
#include "hal/pinout.h"    // <--- IMPORTANTE: Aquí están definidos LED_RED_PIN, etc.
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// TODO: Cuando tengamos la librería de la pantalla, descomentad esta línea:
// #include "drivers/oled/NOMBRELIBRERIA"

void HAL_output_init(void) {
    // --- 1. CONFIGURACIÓN DE LEDS Y BUZZER ---
    // Usamos los nombres que definiste en pinout.h
    const uint pins_salida[] = {LED_RED_PIN, LED_ORANGE_PIN, LED_GREEN_PIN, BUZZER_PIN};
    
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
    
    // i2c_init(OLED_I2C_PORT, OLED_BAUDRATE); // Usando constantes de pinout.h
    // gpio_set_function(OLED_SDA_PIN, GPIO_FUNC_I2C);
    // gpio_set_function(OLED_SCL_PIN, GPIO_FUNC_I2C);
    // gpio_pull_up(OLED_SDA_PIN);
    // gpio_pull_up(OLED_SCL_PIN);
    
    // NOMBRELIBRERIA_init(); // <--- Llamada a la libreria
}

void HAL_set_system_state(SystemState_t state) {
    // Apagamos todo para asegurar un estado limpio antes de encender lo nuevo
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_ORANGE_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
    gpio_put(BUZZER_PIN, 0);

    /* * TAREA JOSECHU/PABLO: 
     * Rellenad el switch para encender lo que toque en cada caso.
     * NOTA DEL EQUIPO: Ya hemos dejado programados los LEDs y el Buzzer, 
     * falta implementar la pantalla.
     */

    switch (state) {
        case STATE_GREEN:
            // TODO: Encender LED Verde -> HECHO
            gpio_put(LED_GREEN_PIN, 1);
            
            // TODO: Escribir "SEGURO" en la pantallita
            // oled_print("SEGURO");
            break;

        case STATE_AMBER:
            // TODO: Encender LED Ámbar -> HECHO
            gpio_put(LED_ORANGE_PIN, 1);
            
            // TODO: Hacer sonar el Buzzer bajito -> (De momento apagado en precaución)
            // gpio_put(BUZZER_PIN, 0); 

            // TODO: Escribir "PRECAUCION" en la pantallita
            // oled_print("PRECAUCION");
            break;

        case STATE_RED:
            // TODO: Encender LED Rojo -> HECHO
            gpio_put(LED_RED_PIN, 1);
            
            // TODO: Encender Buzzer a todo volumen -> HECHO
            gpio_put(BUZZER_PIN, 1); 
            
            // TODO: Escribir "PELIGRO" en la pantallita
            // oled_print("PELIGRO");
            break;
    }
}
