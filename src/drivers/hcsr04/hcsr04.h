/*
 * Archivo: hcsr04.h
 * Descripción: Cabecera del driver. Interfaz limpia y sencilla.
 */

#ifndef HCSR04_H
#define HCSR04_H

// Inicializa los pines (los coge internamente de pinout.h)
void DRIVER_hcsr04_init(void);

// Lee la distancia. Devuelve el valor en cm o -1.0 si falla.
float DRIVER_hcsr04_read(void);

#endif // HCSR04_H
