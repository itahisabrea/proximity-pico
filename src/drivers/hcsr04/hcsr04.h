/*
 * Archivo: hcsr04.h
 * Descripción: Cabecera del driver del sensor. Definimos las funciones que puede usar el resto del programa.
 */

#ifndef HCSR04_H
#define HCSR04_H

// Inicializa los pines del sensor (Trigger salida, Echo entrada)
void DRIVER_hcsr04_init(void);

// Lanza el pulso, mide el tiempo y devuelve la distancia en cm
float DRIVER_hcsr04_read(void);

#endif // HCSR04_H
