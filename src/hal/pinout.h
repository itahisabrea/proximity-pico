/* Definición de pines y mapa hardware.
Asignación de pines lógicos de la raspberry
*/

#ifndef PINOUT_H //Guarda para evitar duplicados al compilar
#define PINOUT_H 

// -------------Sensor de distancia-------------//
//Trigger: pin de salida 
#define HCSR04_TRIG_PIN 2 
//Echo: pin de entrada
#define HCSR04_ECHO_PIN 3

// -------------Pantalla OLED-------------//
//Bloque I2C de la raspberry pi pico
#define OLED_I2C_PORT i2c0
#define OLED_SDA_PIN 0
#define OLED_SCL_PIN 1
#define OLED_BAUDRATE 400000

// ------------Semaforo de leds-------------//
//Rojo: peligro, distancia < 5cm
#define LED_RED_PIN 16
//Naranja: precaución, 5cm<distancia<15cm
#define LED_ORANGE_PIN 17
//Verde: seguro, distancia > 15cm
#define LED_GREEN_PIN 18

// -------------Buzzer-------------//
#define BUZZER_PIN 15

#endif
