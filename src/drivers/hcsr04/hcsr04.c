/*
 * Archivo: hcsr04.c
 * Descripción: Implementación del driver de bajo nivel para el sensor HC-SR04.
 */

#include "drivers/hcsr04/hcsr04.h"
#include "pico/stdlib.h"
#include <stdio.h>

void DRIVER_hcsr04_init(void) {
    // TODO: configurar los pines Trigger y Echo aquí.
    #warning "hcsr04.c: Pendiente la configuración de GPIOs."
}

float DRIVER_hcsr04_read(void) {
    // TODO: implementar la lógica de:
    // 1. Pulso en Trigger.
    // 2. Medir tiempo que dura el pulso en Echo.
    // 3. Convertir tiempo a distancia (Distancia = tiempo * velocidad_sonido / 2).
    #warning "hcsr04.c: Pendiente la lógica de medición."
  
    return 0.0f; // Devolver 0.0 mientras está vacío
}
