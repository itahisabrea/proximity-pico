/*
 * Archivo: hal_output.c
 * Descripción: Implementación del control de luces, sonido y pantalla.
 */

#include "hal/hal_output.h"
#include "hal/pinout.h"
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/i2c.h"
#include "drivers/oled/ssd1306.h"

#include "pico/time.h"

// --- 2. VARIABLES Y FUNCIONES DEL BUZZER (TU CÓDIGO AQUÍ) ---

// Control del parpadeo del buzzer (activo)
static repeating_timer_t temporizador_buzzer;
static bool parpadeo_buzzer_activo = false;

// Alterna ON/OFF del buzzer activo (salida digital)
static bool alternar_buzzer_cb(repeating_timer_t *t) {
    static bool nivel = false;
    nivel = !nivel;
    // Usamos BUZZER_PIN que viene de pinout.h
    gpio_put(BUZZER_PIN, nivel); 
    return true;  // seguir repitiendo
}

// Inicia el parpadeo del buzzer con un periodo total en ms
static void iniciar_parpadeo_buzzer(int periodo_ms) {
    if (parpadeo_buzzer_activo) return;

    // Llamada cada periodo_ms/2 para tener 50% de ciclo
    bool ok = add_repeating_timer_ms(-(periodo_ms / 2), alternar_buzzer_cb, NULL, &temporizador_buzzer);
    if (ok) {
        parpadeo_buzzer_activo = true;
    } else {
        gpio_put(BUZZER_PIN, 0);
    }
}

// Detiene el parpadeo y apaga el buzzer
static void detener_parpadeo_buzzer(void) {
    if (!parpadeo_buzzer_activo) {
        // Aseguramos que esté apagado aunque no parpadee
        gpio_put(BUZZER_PIN, 0); 
        return;
    }

    cancel_repeating_timer(&temporizador_buzzer);
    parpadeo_buzzer_activo = false;
    gpio_put(BUZZER_PIN, 0); // asegurar apagado final
}

// --- 3. VARIABLES DE PANTALLA ---
struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

uint8_t ssd[ssd1306_buffer_length]; 

// --- 4. FUNCIONES DE PANTALLA ---
void oled_print_text(const char *msg) {
    memset(ssd, 0, ssd1306_buffer_length);
    ssd1306_draw_string(ssd, 5, 0, (char*)msg); 
    render_on_display(ssd, &frame_area);
}

// --- 5. INICIALIZACIÓN ---
void HAL_output_init(void) {
    // Configuración GPIOs
    const uint pins_salida[] = {LED_RED_PIN, LED_ORANGE_PIN, LED_GREEN_PIN, BUZZER_PIN};
    for (int i = 0; i < 4; i++) {
        gpio_init(pins_salida[i]);
        gpio_set_dir(pins_salida[i], GPIO_OUT);
        gpio_put(pins_salida[i], 0);
    }

    // Configuración OLED (I2C0)
    i2c_init(i2c0, ssd1306_i2c_clock * 1000);
    gpio_set_function(OLED_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SDA_PIN);
    gpio_pull_up(OLED_SCL_PIN);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    memset(ssd, 0, ssd1306_buffer_length);
}

// --- 6. CONTROL DE ESTADOS (AQUÍ USAMOS TU CÓDIGO) ---
void HAL_set_system_state(SystemState_t state) {
    // Apagamos LEDs (el buzzer lo gestionamos abajo)
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_ORANGE_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);

    // IMPORTANTE: Detenemos el buzzer por defecto.
    // Si el estado nuevo requiere buzzer, lo encendemos dentro del switch.
    // Si no, se queda apagado gracias a esta llamada.
    detener_parpadeo_buzzer();

switch (state) {
        case STATE_GREEN:
            gpio_put(LED_GREEN_PIN, 1);
            oled_print_text("SEGURO");
            // Buzzer apagado (ya lo hizo detener_parpadeo_buzzer arriba)
            break;

        case STATE_AMBER:
            gpio_put(LED_ORANGE_PIN, 1);
            oled_print_text("PRECAUCION");
            //Pitido lento en ambar
            iniciar_parpadeo_buzzer(1000); // 1 segundo (lento)
            break;

        case STATE_RED:
            gpio_put(LED_RED_PIN, 1);
            oled_print_text("PELIGRO");
            gpio_put(BUZZER_PIN, 1); 
            break;
    }
}
