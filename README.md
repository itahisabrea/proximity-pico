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

## 👥 Equipo y Roles

Adaptando la metodología al flujo de trabajo del equipo, se definen los siguientes roles técnicos:

* **Itahisa** (@itahisabrea)
    * **Rol:** Líder de Integración.
    * *Funciones:* Coordinación del repositorio Git, gestión de ramas (branches) y fusión final de módulos.
* **Uxía** (@uxiibl)
    * **Rol:** Responsable Hardware y Señales.
    * *Funciones:* Diseño del circuito, montaje en protoboard, conexiones y caracterización del sensor.
* **Josechu** (@RetornoDeLinea007) y **Pablo** (@Arknarr)
    * **Rol:** Responsables de Software y Tiempo Real.
    * *Funciones:* Desarrollo de la Máquina de Estados (FSM), drivers de actuadores, gestión de temporizadores e implementación de la lógica de control.

### ✅ Validación y Documentación (Responsabilidad Compartida)
Siguiendo un enfoque de calidad total, la fase de **Validación y Documentación** es asumida por **todo el equipo** de forma transversal:
* **Pruebas Cruzadas:** Cada miembro valida el código/hardware desarrollado por otro compañero.
* **Documentación:** Todos contribuyen a la redacción de la memoria técnica y la grabación de la demo final.

## 👥 Autores
Uxía Barja López
Itahisa Brea Portals
José Cruz Vizcaíno
Pablo González Valderrábano
---
*Proyecto desarrollado en la Universidade de Vigo - Curso 2025/2026*
