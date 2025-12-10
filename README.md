# 🚗 Sistema de Detección de Proximidad

Proyecto para la asignatura de **Sistemas de Control en Tiempo Real**. 
Este sistema implementa un "asistente de aparcamiento" utilizando una **Raspberry Pi Pico**, que mide la distancia mediante ultrasonidos y alerta al usuario mediante señales visuales (LEDs + Pantalla OLED) y sonoras (Buzzer).

## 🛠️ Hardware

Lista de materiales utilizados en el proyecto:

* **Microcontrolador:** Raspberry Pi Pico (RP2040)
* **Sensor:** Ultrasonido HC-SR04
* **Pantalla:** OLED I2C 1.3" (Driver **NO SE SABE**)
* **Actuadores:**
    * 3x LEDs (Rojo, Ámbar, Verde) con resistencias de 330Ω en serie.
    * 1x Buzzer Activo.
* **Varios:** Protoboard, cables jumper.

> **Nota de Alimentación:** El sensor HC-SR04 se alimenta a **5V (VBUS, Pin 40)**, mientras que la pantalla OLED va a **3.3V (Pin 36)**.

## 🏗️ Arquitectura del Software

El proyecto sigue una estructura modular estricta para garantizar la escalabilidad y el mantenimiento:

    ├── app/        # Capa de Aplicación (Lógica de control y FSM)
    ├── hal/        # Hardware Abstraction Layer (Interfaz genérica)
    └── drivers/    # Drivers de bajo nivel (HC-SR04, DRIVER PANTALLA)

### ⚠️ Regla de Oro de Integración
Para evitar dependencias cruzadas ("código espagueti"), el equipo sigue esta jerarquía:
1.  **APP** solo se comunica con **HAL**.
2.  **HAL** traduce las órdenes y se comunica con los **DRIVERS**.
3.  **DRIVERS** son los únicos que tocan los registros físicos del microcontrolador.

## 🔌 Conexiones (Pinout)

Configuración física de los pines según el diseño hardware:

| Componente | Pin Raspberry (GP) | Pin Físico | Notas Conexión |
| :--- | :--- | :--- | :--- |
| **OLED SDA** | GP0 | 1 | Directo |
| **OLED SCL** | GP1 | 2 | Directo |
| **Sensor TRIG** | GP2 | 4 | Directo |
| **Sensor ECHO** | GP3 | 5 | ⚠️ **Divisor de Tensión** (5V -> 3.3V) |
| **Buzzer** | GP15 | 20 | Directo |
| **LED Rojo** | GP16 | 21 | Resistencia 330Ω |
| **LED Ámbar** | GP17 | 22 | Resistencia 330Ω |
| **LED Verde** | GP18 | 24 | Resistencia 330Ω |

## 🚦 Lógica de Control

El sistema opera bajo los siguientes estados según la distancia medida:

| Zona | Distancia | LED | Pantalla | Buzzer |
| :--- | :--- | :--- | :--- | :--- |
| **SEGURA** | > 15 cm | 🟢 Verde | "-" | Off |
| **PRECAUCIÓN** | 5 - 15 cm | 🟠 Ámbar | "CUIDADO!" | Intermitente |
| **PELIGRO** | < 5 cm | 🔴 Rojo | "PARA!!" | Rápido/Continuo |

## 🚀 Instalación y Uso

Requisitos: **CMake**, **GCC-ARM-NONE-EABI** y **Pico SDK**.

1.  **Clonar el repositorio:**
    ```bash
    git clone https://github.com/itahisabrea/proximity-pico
    ```
2.  **Compilar:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
3.  **Flashear:**
    * Mantener pulsado el botón `BOOTSEL` de la Pico y conectarla al USB.
    * Copiar el archivo `sctr_app.uf2` generado en la carpeta `build` a la unidad de almacenamiento.

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
Uxía Barja López <br>
Itahisa Brea Portals <br>
José Cruz Vizcaíno <br>
Pablo González Valderrábano <br>

---
*Proyecto desarrollado en la Universidade de Vigo - Curso 2025/2026*
