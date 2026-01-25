/*
 * Archivo: hal_output.h
 * Descripción: Control de LEDs, Buzzer y Pantalla.
 * Los pines están definidos en "hal/pinout.h".
 */

#ifndef HAL_OUTPUT_H
#define HAL_OUTPUT_H

#include <stdint.h> 

// Estados posibles del sistema (Verde, Naranja, Rojo)
typedef enum {
    STATE_GREEN,
    STATE_AMBER,
    STATE_RED
} SystemState_t;

// Función para configurar los pines de salida al principio
void HAL_output_init(void);

// Función que enciende/apaga cosas según el estado (state)
void HAL_set_system_state(SystemState_t state);

#endif 
