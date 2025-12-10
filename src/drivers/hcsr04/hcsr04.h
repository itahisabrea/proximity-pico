/*
 * Archivo: hcsr04.h
 * Descripción: Interfaz del driver de bajo nivel para el sensor HC-SR04.
 */

#ifndef HCSR04_H
#define HCSR04_H

#include <stdint.h>

// --- DEFINICIÓN DE PINES (SEGÚN PDF) ---
// Trigger conectado a GP2 (Pin 4)
#define HCSR04_TRIG_PIN 2 
// Echo conectado a GP3 (Pin 5)
#define HCSR04_ECHO_PIN 3 

/**
 * @brief Configura los pines GPIO para el sensor.
 */
void DRIVER_hcsr04_init(void);

/**
 * @brief Mide la distancia de forma cruda (sin filtrado).
 * @return Distancia medida en centímetros (cm).
 */
float DRIVER_hcsr04_read(void);

#endif // HCSR04_H
