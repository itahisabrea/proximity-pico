/*
 * Archivo: hal_output.h
 * Descripción: Manejo de LEDs, Buzzer y Pantalla.
 */

#ifndef HAL_OUTPUT_H
#define HAL_OUTPUT_H

// --- DEFINICIÓN DE PINES  ---
#define PIN_LED_RED     16  // GP16
#define PIN_LED_AMBER   17  // GP17
#define PIN_LED_GREEN   18  // GP18
#define PIN_BUZZER      15  // GP15

// Pantalla I2C (GP0 y GP1)
#define I2C_PORT        i2c0
#define PIN_I2C_SDA     0
#define PIN_I2C_SCL     1

typedef enum {
    STATE_GREEN,
    STATE_AMBER,
    STATE_RED
} SystemState_t;

void HAL_output_init(void);
void HAL_set_system_state(SystemState_t state);

#endif 
