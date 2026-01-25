#include "hal_sensor.h"
#include "driver_distance.h" // Incluimos el driver de Uxía
#include "pinout.h"          // Incluimos pines

// Instancia privada del sensor
static distance_sensor_t g_sensor_hw = {
    .trig_gpio = HCSR04_TRIG_PIN,
    .echo_gpio = HCSR04_ECHO_PIN
};

void HAL_sensor_init(void) {
    // Inicializamos el driver usando la estructura configurada
    distance_init(&g_sensor_hw);
}

float HAL_get_distance_cm(void) {
    float raw_val;
    
    // Llamamos al driver
    bool ok = distance_read_cm(&g_sensor_hw, &raw_val);
    
    // Si falla, devolvemos -1.0 para que la Máquina de Estados lo ignore
    if (!ok) {
        return -1.0f;
    }
    
    return raw_val;
}
