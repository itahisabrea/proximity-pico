# 🚗 Sistema de Detección de Proximidad

Proyecto para la asignatura de **Sistemas de Control en Tiempo Real**. 
Este sistema implementa un "asistente de aparcamiento" utilizando una **Raspberry Pi Pico**, que mide la distancia mediante ultrasonidos y alerta al usuario mediante señales visuales (LEDs + Pantalla OLED) y sonoras (Buzzer).

## 🛠️ Hardware

Lista de materiales utilizados en el proyecto:

* **Microcontrolador:** Raspberry Pi Pico (RP2040)
* **Sensor:** Ultrasonido 
* **Pantalla:** OLED I2C (Driver **SH1106**)
* **Actuadores:**
    * 3x LEDs (Rojo, Ámbar, Verde)
    * 1x Buzzer 
* **Varios:** Resistencias, Cables, Protoboard.

## 🔌 Conexiones (Pinout Inicial)


## 🚦 Lógica de Control
El sistema opera bajo los siguientes estados según la distancia medida:
| Zona | Distancia | LED | Pantalla | Buzzer |
| :--- | :--- | :--- | :--- | :--- |
| **SEGURA** | > 15 cm | 🟢 Verde | "-" | Off |
| **PRECAUCIÓN** | 5 - 15 cm | 🟠 Ámbar | "CUIDADO!" | Intermitente |
| **PELIGRO** | < 5 cm | 🔴 Rojo | "PARA!!" | Rápido/Continuo |

## 🚀 Instalación y Uso


## 👥 Autores

---
*Proyecto desarrollado en la Universidade de Vigo - Curso 2025/2026*
