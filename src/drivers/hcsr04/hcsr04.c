/*
 * Archivo: hcsr04.c
 * Descripción: Implementación del driver para el sensor HC-SR04.
 * Aquí es donde se "habla" directamente con los pines de la Raspberry.
 */

#include "drivers/hcsr04/hcsr04.h"
#include "hal/pinout.h"            
#include "pico/stdlib.h"           
#include <stdio.h>

void DRIVER_hcsr04_init(void) {
    // TODO: Configurar los pines GPIO
    // 1. Inicializar Trigger y Echo.
    // 2. Poner Trigger como SALIDA y Echo como ENTRADA.
    // 3. Poner Trigger a 0 para empezar limpio.
}

float DRIVER_hcsr04_read(void) {
    // TODO: Lógica de medición
    // 1. Enviar pulso de 10us por Trigger.
    // 2. Esperar a que Echo se ponga en ALTO.
    // 3. Medir cuánto tiempo se queda en ALTO.
    // 4. Calcular distancia.
    
    return 0.0f; // Devolvemos 0 por ahora
}
