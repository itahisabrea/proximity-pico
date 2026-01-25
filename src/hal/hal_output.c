/*
 * Archivo: hal_output.c
 * Descripción: Implementación corregida para evitar reinicios constantes
 */

#include "hal/hal_output.h"
#include "hal/pinout.h"
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/i2c.h"
#include "drivers/oled/ssd1306.h"
#include "pico/time.h"

// --- VARIABLES Y FUNCIONES DEL BUZZER ---
static repeating_timer_t temporizador_buzzer;
static bool parpadeo_buzzer_activo = false;

static bool alternar_buzzer_cb(repeating_timer_t *t) {
    static bool nivel = false;
    nivel = !nivel;
    gpio_put(BUZZER_PIN, nivel); 
    return true; 
}

static void iniciar_parpadeo_buzzer(int periodo_ms) {
    if (parpadeo_buzzer_activo) return;

    bool ok = add_repeating_timer_ms(-(periodo_ms / 2), alternar_buzzer_cb, NULL, &temporizador_buzzer);
    if (ok) {
        parpadeo_buzzer_activo = true;
    } else {
        gpio_put(BUZZER_PIN, 0);
    }
}

static void detener_parpadeo_buzzer(void) {
    // Solo cancelamos si realmente hay un temporizador activo
    if (parpadeo_buzzer_activo) {
        cancel_repeating_timer(&temporizador_buzzer);
        parpadeo_buzzer_activo = false;
    }
    // Aseguramos silencio
    gpio_put(BUZZER_PIN, 0); 
}

// --- VARIABLES DE PANTALLA ---
struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};
uint8_t ssd[ssd1306_buffer_length]; 

void oled_print_text(const char *msg) {
    memset(ssd, 0, ssd1306_buffer_length);
    ssd1306_draw_string(ssd, 5, 0, (char*)msg); 
    render_on_display(ssd, &frame_area);
}

// --- INICIALIZACIÓN ---
void HAL_output_init(void) {
    const uint pins_salida[] = {LED_RED_PIN, LED_ORANGE_PIN, LED_GREEN_PIN, BUZZER_PIN};
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_salida[i]);
        gpio_set_dir(pins_salida[i], GPIO_OUT);
        gpio_put(pins_salida[i], 0);
    }

    i2c_init(i2c0, ssd1306_i2c_clock * 1000);
    gpio_set_function(OLED_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SDA_PIN);
    gpio_pull_up(OLED_SCL_PIN);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    memset(ssd, 0, ssd1306_buffer_length);
}

// --- CONTROL DE ESTADOS CORREGIDO ---
void HAL_set_system_state(SystemState_t state) {
    // 1. Apagamos LEDs
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_ORANGE_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);

    switch (state) {
        case STATE_GREEN:
            gpio_put(LED_GREEN_PIN, 1);
            oled_print_text("SEGURO");
            
            // Aquí SI queremos silencio total
            detener_parpadeo_buzzer(); 
            break;

        case STATE_AMBER:
            gpio_put(LED_ORANGE_PIN, 1);
            oled_print_text("PRECAUCION");
            
            // Aquí iniciamos el parpadeo.
            iniciar_parpadeo_buzzer(1000); 
            break;

        case STATE_RED:
            gpio_put(LED_RED_PIN, 1);
            oled_print_text("PELIGRO");
            
            // 1. Si veníamos de Ámbar, hay que matar el temporizador
            if (parpadeo_buzzer_activo) {
                detener_parpadeo_buzzer();
            }
            
            // 2. Encendemos Fijo
            gpio_put(BUZZER_PIN, 1); 
            break;
    }
}
