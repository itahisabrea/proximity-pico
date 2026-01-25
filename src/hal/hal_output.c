/*
 * Archivo: hal_output.c
 * Descripción: Implementación del control de luces, sonido y pantalla.
 * Responsables: Josechu y Pablo
 */

#include "hal/hal_output.h"
#include "hal/pinout.h"
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/i2c.h"
#include "drivers/oled/ssd1306.h"

struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

uint8_t ssd[ssd1306_buffer_length]; // Buffer de renderizado de la pantalla

void HAL_output_init(void) {
    // --- 1. CONFIGURACIÓN DE LEDS Y BUZZER ---
    const uint pins_salida[] = {LED_RED_PIN, LED_ORANGE_PIN, LED_GREEN_PIN, BUZZER_PIN};
    
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_salida[i]);
        gpio_set_dir(pins_salida[i], GPIO_OUT);
        gpio_put(pins_salida[i], 0); // Empezamos con todo apagado
    }

    // --- 2. CONFIGURACIÓN DE LA PANTALLA ---
    i2c_init(i2c0, ssd1306_i2c_clock * 1000);
    gpio_set_function(0, GPIO_FUNC_I2C); // SDA
    gpio_set_function(1, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(OLED_SDA_PIN);
    gpio_pull_up(OLED_SCL_PIN);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area); // Preparar el area de renderiado par ael display
    memset(ssd, 0, ssd1306_buffer_length); // Cero en el buffer del display
}

void oled_print_text(const char *msg) {
    // 1. Limpiar el buffer (borrar lo anterior)
    memset(ssd, 0, ssd1306_buffer_length);
    
    // 2. Dibujar el nuevo texto

    ssd1306_draw_string(ssd, 5, 0, (char*)msg); 
    
    // 3. Enviar a la pantalla
    render_on_display(ssd, &frame_area);
}

void HAL_set_system_state(SystemState_t state) {
    // Apagamos todo para asegurar un estado limpio
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_ORANGE_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
    gpio_put(BUZZER_PIN, 0);

switch (state) {
        case STATE_GREEN:
            // Caso Seguro
            gpio_put(LED_GREEN_PIN, 1);
            oled_print_text("SEGURO");
            break;

        case STATE_AMBER:
            // Caso Precaución
            gpio_put(LED_ORANGE_PIN, 1);
            oled_print_text("PRECAUCION");
            break;

        case STATE_RED:
            // Caso Peligro
            gpio_put(LED_RED_PIN, 1);
            gpio_put(BUZZER_PIN, 1); 
            oled_print_text("PELIGRO");
            break;
    }
}
