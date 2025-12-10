/*
 * Archivo: hal_sensor.h
 * Descripción: Interfaz para el sensor ultrasónico (HC-SR04).
 En principio este archivo no se debería modificar (revisarlo y esas cosas)
 */

#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H

#include <stdint.h>

/**
 * @brief Inicializa los pines del sensor (Trigger y Echo).
 */
void HAL_sensor_init(void);

/**
 * @brief Mide la distancia y aplica el filtrado necesario.
 * @return Distancia medida en centímetros (cm).
 */
float HAL_get_distance_cm(void);

#endif 
