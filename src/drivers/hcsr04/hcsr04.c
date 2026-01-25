/*
 * Archivo: hcsr04.c
 * Descripción: Implementación del driver HC-SR04 con lógica robusta (timeouts).
 */

#include "hcsr04.h"      
#include "hal/pinout.h"  
#include "pico/stdlib.h" 

// Función interna auxiliar 
static void internal_pulse_trig(void) {
    gpio_put(HCSR04_TRIG_PIN, 0);
    sleep_us(2);
    gpio_put(HCSR04_TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(HCSR04_TRIG_PIN, 0);
}

void DRIVER_hcsr04_init(void) {
    // 1. Configurar Trigger como SALIDA
    gpio_init(HCSR04_TRIG_PIN);
    gpio_set_dir(HCSR04_TRIG_PIN, GPIO_OUT);
    gpio_put(HCSR04_TRIG_PIN, 0);

    // 2. Configurar Echo como ENTRADA
    gpio_init(HCSR04_ECHO_PIN);
    gpio_set_dir(HCSR04_ECHO_PIN, GPIO_IN);

    sleep_ms(50); // Pequeña espera de cortesía para que el sensor arranque
}

float DRIVER_hcsr04_read(void) {
    // 1. Lanzar el pulso
    internal_pulse_trig();

    // 2. Esperar a que el Echo se ponga en ALTO (timeout 30 ms)
    // Usamos la lógica de timeouts de "driver_distance.c"
    absolute_time_t t0 = get_absolute_time();
    while (gpio_get(HCSR04_ECHO_PIN) == 0) {
        if (absolute_time_diff_us(t0, get_absolute_time()) > 30000) {
            return -1.0f; // Error: El sensor no respondió
        }
    }

    // 3. Medir cuánto tiempo se queda en ALTO (timeout 30 ms)
    absolute_time_t t1 = get_absolute_time();
    while (gpio_get(HCSR04_ECHO_PIN) == 1) {
        if (absolute_time_diff_us(t1, get_absolute_time()) > 30000) {
            return -1.0f; // Error: El pulso duró demasiado (fuera de rango)
        }
    }
    absolute_time_t t2 = get_absolute_time();

    // 4. Calcular distancia
    int64_t pulse_us = absolute_time_diff_us(t1, t2);
    float cm = (float)pulse_us / 58.0f;

    // 5. Filtrar resultados locos
    if (cm < 0.5f || cm > 400.0f) {
        return -1.0f; // Error: Medida inverosímil
    }

    return cm;
}
