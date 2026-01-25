/*
 * Archivo: hal_sensor.c
 * Descripción: Capa de abstracción del sensor.
 * Conecta la aplicación con el driver HC-SR04 modificado.
 */

#include "hal/hal_sensor.h"
#include "drivers/hcsr04/hcsr04.h" // Incluimos el driver con la lógica del Driver de Uxi

void HAL_sensor_init(void) {
    DRIVER_hcsr04_init();
}

float HAL_get_distance_cm(void) {

    return DRIVER_hcsr04_read();
}
