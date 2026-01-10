/*
 * Archivo: main.c
 * Descripción: Máquina de estados
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hal/hal_sensor.h"
#include "hal/hal_output.h"

/* 1. ESTADOS */
enum state {
    ST_GREEN = 0,
    ST_AMBER,
    ST_RED,
    STATE_MAX
};

/* 2. EVENTOS */
enum event {
    EV_NONE = 0,
    EV_DIST_SAFE,   // Distancia > 15
    EV_DIST_WARN,   // 5 < Distancia < 15
    EV_DIST_CRIT,   // Distancia < 5
    EVENT_MAX
};

/* 3. ACCIONES (Wrappers para llamar al HAL) */

void act_set_green(void) {
    HAL_set_system_state(STATE_GREEN); // Llama a tu HAL
    printf("ACCION: Todo Verde\n");
}

void act_set_amber(void) {
    HAL_set_system_state(STATE_AMBER);
    printf("ACCION: Alerta Naranja\n");
}

void act_set_red(void) {
    HAL_set_system_state(STATE_RED);
    printf("ACCION: Peligro Rojo\n");
}

/* 4. TRANSICIONES */
// Transición genérica para ir a VERDE
enum state trans_to_green(void) {
    act_set_green();
    return ST_GREEN;
}

// Transición genérica para ir a ÁMBAR
enum state trans_to_amber(void) {
    act_set_amber();
    return ST_AMBER;
}

// Transición genérica para ir a ROJO
enum state trans_to_red(void) {
    act_set_red();
    return ST_RED;
}

/* 5. TABLA DE TRANSICIONES (Matriz de Punteros) */
/* Filas = Estado Actual, Columnas = Evento que ocurre */

enum state (*trans_table[STATE_MAX][EVENT_MAX])(void) = {
    // Si estoy en VERDE...
    [ST_GREEN] = {
        [EV_DIST_SAFE] = trans_to_green,  // Sigo verde
        [EV_DIST_WARN] = trans_to_amber,  // Cambio a ambar
        [EV_DIST_CRIT] = trans_to_red,    // Cambio a rojo
    },
    // Si estoy en ÁMBAR...
    [ST_AMBER] = {
        [EV_DIST_SAFE] = trans_to_green,  // Vuelvo a verde
        [EV_DIST_WARN] = trans_to_amber,  // Sigo ambar
        [EV_DIST_CRIT] = trans_to_red,    // Empeoro a rojo
    },
    // Si estoy en ROJO...
    [ST_RED] = {
        [EV_DIST_SAFE] = trans_to_green,  // Vuelvo a verde
        [EV_DIST_WARN] = trans_to_amber,  // Mejoro a ambar
        [EV_DIST_CRIT] = trans_to_red,    // Sigo rojo
    }
};

/* 6. PARSEADOR DE EVENTOS */
enum event event_parser(float dist_cm) {
    if (dist_cm > 15.0f) return EV_DIST_SAFE;
    if (dist_cm > 5.0f)  return EV_DIST_WARN;
    if (dist_cm >= 0.0f) return EV_DIST_CRIT; 
    return EV_NONE; 
}

/* MAIN */
int main(void) {
    stdio_init_all();
    HAL_sensor_init();
    HAL_output_init();
    
    printf("Sistema iniciado.\n");
    // Estado inicial
    act_set_green(); 
    enum state st = ST_GREEN;

    // Bucle infinito
    for (;;) {
        // A. LEER
        float dist = HAL_get_distance_cm();
        // B. PARSEAR 
        enum event ev = event_parser(dist);
        // C. BUSCAR EN TABLA 
        enum state (*tr)(void) = trans_table[st][ev];
        // D. EJECUTAR
        if (tr != NULL) {
            st = tr();
        } 
        sleep_ms(100); //Pausita por si satura
    }

    return 0;
}
