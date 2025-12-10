/*
 * Archivo: hal_output.h
 * Descripción: Interfaz de abstracción para todas las salidas (LEDs, Buzzer, Pantalla).
 */

#ifndef HAL_OUTPUT_H
#define HAL_OUTPUT_H

// Define los 3 estados principales del sistema
typedef enum {
    STATE_GREEN,    // Distancia segura
    STATE_AMBER,    // Distancia de precaución
    STATE_RED       // Distancia crítica
} SystemState_t;

/**
 * @brief Inicializa el hardware de todas las salidas (GPIO de LEDs/Buzzer, I2C de pantalla).
 */
void HAL_output_init(void);

/**
 * @brief Actualiza todos los dispositivos de salida al nuevo estado.
 * @param state El estado a aplicar (VERDE, ÁMBAR o ROJO).
 */
void HAL_set_system_state(SystemState_t state);

#endif 
