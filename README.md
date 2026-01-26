# 🚗 Sistema de Detección de Proximidad

Proyecto para la asignatura de **Sistemas de Control en Tiempo Real**. 
Este sistema implementa un "asistente de aparcamiento" utilizando una **Raspberry Pi Pico**, que mide la distancia mediante ultrasonidos y alerta al usuario mediante señales visuales (LEDs + Pantalla OLED) y sonoras (Buzzer).

## 🛠️ Hardware

Lista de materiales utilizados en el proyecto:

* **Microcontrolador:** Raspberry Pi Pico (RP2040)
* **Sensor:** Ultrasonido HC-SR04
* **Pantalla:** OLED I2C 1.3" (Driver **SSD1306**)
* **Actuadores:**
    * 3x LEDs (Rojo, Ámbar, Verde) con resistencias de 220Ω en serie.
    * 1x Buzzer Activo.
* **Varios:** Protoboard, cables.

> **Nota de Alimentación:** El sensor HC-SR04 se alimenta a **5V (VBUS, Pin 40)**, mientras que la pantalla OLED va a **3.3V (Pin 36)**.

<img width="627" height="749" alt="image" src="https://github.com/user-attachments/assets/0c84c335-ae65-4d01-99a2-ebf89d786eee" />

<img width="2048" height="1536" alt="image" src="https://github.com/user-attachments/assets/20cb3368-d50b-4204-92db-d609c49867d1" />




## 🏗️ Arquitectura del Software

El proyecto sigue una estructura modular estricta para garantizar la escalabilidad y el mantenimiento:

```text
.
├── CMakeLists.txt
└── src/
    ├── app/
         └── main.c
    ├── hal/
         ├── hal_output.c
         ├── hal_output.h
         ├── hal_sensor.c
         ├── hal_sensor.h
         └── pinout.h
    └── drivers/
         ├── hcsr04/
            ├── hcsr04.h
            └── hcsr04.c
         └── oled/
            ├── font.h
            ├── i2c.h
            ├── ssd1306.h
            └── ssd1306.c
```

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
| **OLED VDD** | 3V3 | 36 | Directo |
| **OLED GND** | GND | 38 | Directo |
| **Sensor GND** | GND | 3 | Directo |
| **Sensor TRIG** | GP2 | 4 | Directo |
| **Sensor ECHO** | GP3 | 5 | ⚠️ **Divisor de Tensión** (5V -> 3.3V) |
| **Sensor VCC** | VBUS | 40 | Directo |
| **Buzzer** | GP15 | 20 | Directo |
| **LED Rojo** | GP16 | 21 | Resistencia 220Ω |
| **LED Ámbar** | GP17 | 22 | Resistencia 220Ω |
| **LED Verde** | GP18 | 24 | Resistencia 220Ω |

## 🚦 Lógica de Control

El sistema opera bajo los siguientes estados según la distancia medida:

| Zona | Distancia | LED | Pantalla | Buzzer |
| :--- | :--- | :--- | :--- | :--- |
| **SEGURA** | > 15 cm | 🟢 Verde | "SEGURO" | Off |
| **PRECAUCIÓN** | 5 - 15 cm | 🟠 Ámbar | "PRECAUCION" | Intermitente (1000ms) |
| **PELIGRO** | < 5 cm | 🔴 Rojo | "PELIGRO" | Continuo |

## ⭐ Características Destacadas

* **Máquina de Estados:** Se ha implementado una matriz de punteros a función para transiciones deterministas y limpias.
  
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
    * **Rol:** Responsable Hardware, Señales y Pruebas Funcionales.
    * *Funciones:* Diseño del circuito, montaje en protoboard, pruebas funcionales, conexiones y caracterización del sensor.
* **Josechu** (@RetornoDeLinea007) y **Pablo** (@Arknarr)
    * **Rol:** Responsables de Software y Tiempo Real.
    * *Funciones:* Desarrollo de la Máquina de Estados (FSM), drivers de actuadores, gestión de temporizadores e implementación de la lógica de control.

### ✅ Validación y Documentación (Responsabilidad Compartida)
Siguiendo un enfoque de calidad total, la fase de **Validación y Documentación** es asumida por **todo el equipo** de forma transversal:
* **Pruebas Cruzadas:** Cada miembro valida el código/hardware desarrollado por otro compañero.
* **Documentación:** Todos contribuyen a la redacción de la memoria técnica y la grabación de la demo final.

## 🐥 Demostración

https://github.com/user-attachments/assets/9c223d88-2950-4b62-ab8a-f47f5badd737


## 📜 Créditos y Referencias

El desarrollo de este proyecto se ha apoyado en librerías de código abierto:

* **Driver OLED (SSD1306):** La biblioteca para el control de la pantalla OLED está basada en el trabajo de [Eudivanmelo](https://github.com/Eudivanmelo).
  
## 👥 Autores
Uxía Barja López <br>
Itahisa Brea Portals <br>
José Cruz Vizcaíno <br>
Pablo González Valderrábano <br>

---
*Proyecto desarrollado en la Universidade de Vigo - Curso 2025/2026*
