/*
 * Archivo: hal_sensor.c
 * Qué hace: Hace de puente entre nuestro código principal y el driver del sensor.
 * Así si cambiamos el sensor mañana, solo tocamos este archivo.
 */

#include "hal/hal_sensor.h"
#include "drivers/hcsr04/hcsr04.h" // Aquí están las funciones de bajo nivel

// Configuración inicial
void HAL_sensor_init(void) {
    // 1. Inicializar el hardware
    // Aquí solo hay que llamar a la función de inicio que está en el driver DRIVER_sensor_init().
    // Si no llamamos a esto, el sensor no arranca.
}

// Función principal para pedir la distancia
float HAL_get_distance_cm(void) {
    float final_distance = 0.0f;
    
    // 2. Pedir el dato crudo
    // Llamar a la función de lectura del driver y guardarlo.
    // float lectura = DRIVER_sensor_read();
    
    // 3. Filtrado (Opcional pero recomendado)
    // El sensor a veces devuelve basura (ceros o números gigantes).Aquí podríamos poner un if simple:
    // Si la lectura es > 400 o < 0, devolvemos la última distancia válida. Si no, devolvemos la lectura actual.
    
    final_distance = /* poner aquí la variable con el dato procesado */;
    
    return final_distance;
}
