/* * Archivo: main.c
 * Descripción: Cerebro principal del sistema SCTR.
 */

#include <stdio.h>
#include "pico/stdlib.h"       // Librería base de la Raspberry 
#include "hal/hal_sensor.h"    // Interfaz del sensor (Conexión con uxiii)
#include "hal/hal_output.h"    // Interfaz de salidas (Conexión con Josechu)

int main(void) {
    // 1. Inicialización básica de la consola 
    stdio_init_all();

    // 2. Inicialización del Hardware (Aquí llamamos a las capas inferiores)
    printf("Iniciando sistema SCTR...\n");
    
    HAL_sensor_init();  // Prepara los pines del sensor
    HAL_output_init();  // Prepara la pantalla y LEDs

    // 3. Bucle infinito
    while (1) {
        // --- A. LEER ---
        // float distancia = HAL_get_distance_cm();

        // --- B. DECIDIR ---
        // Aquí pondremos los IF/ELSE para decidir si es VERDE, AMBAR o ROJO
        
        // --- C. ACTUAR  ---
        // HAL_set_system_state(estado_decidido);

        // Pequeña pausa (100ms = 10 veces por segundo)
        sleep_ms(100);
    }
    
    return 0;
}
