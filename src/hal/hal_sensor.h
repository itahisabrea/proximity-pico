/*
 * Archivo: hal_sensor.h
 * Descripción: Interfaz pública del sensor de distancia.
 * La aplicación usará estas funciones sin preocuparse del hardware.
 */

#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H

#include <stdint.h>

// Inicializa el hardware del sensor
void HAL_sensor_init(void);

// Mide la distancia en cm aplicando filtrado de errores
float HAL_get_distance_cm(void);

#endif
