# 🐭 ScareMouse Arduino

**ScareMouse Arduino** is the hardware interface for the ScareMouse research platform — a system developed to measure startle reflexes in mice for tinnitus studies at **Loyola University Chicago**.  
This module handles **load cell readings** and **serial communication** with a computer or Raspberry Pi running the GUI software.

---

## ⚙️ Overview

The Arduino collects force data from a load cell using an **HX711 amplifier** and transmits it over serial whenever an **audio stimulus** is played.  
By synchronizing movement data with sound playback, researchers can analyze the **startle reflex magnitude and timing** of test subjects.

---

## 🧩 Features

- Reads precise force data from a **load cell** via HX711.  
- Communicates with **Python-based GUI** or **Raspberry Pi** through serial.  
- Timestamped data output for easy synchronization with auditory cues.  
- Simple, modular code — easily adaptable for different experiment setups.  

---

## 🔌 Hardware Setup

| Component | Description |
|------------|-------------|
| **Arduino** | Main microcontroller for data collection |
| **HX711** | Load cell amplifier module |
| **Load Cell** | Measures subtle movement from the mouse |
| **Speaker / Audio System** | Provides startle stimuli |
| **Raspberry Pi / Computer** | Runs GUI and records data via serial |

Wiring and pin definitions are configurable within the source code.

---

## 💻 Serial Communication

The Arduino continuously monitors the load cell and sends data packets to the connected computer or Raspberry Pi when the GUI triggers playback.  
Each packet includes:
timestamp, weightReading

This allows precise correlation between auditory events and reflex intensity.

---

## 🧠 Research Context

This project supports tinnitus research by providing an **objective, data-driven method** to evaluate treatment effectiveness.  
Developed under the guidance of **Professor Wei-Ming Yu** at **Loyola University Chicago**, ScareMouse bridges hardware sensing and data visualization for biomedical experimentation.

---

## 🗂 Repository Structure

```text
ScareMouseArduino/
├── ScareMouseArduino.ino   # Main Arduino code
├── README.md               # Project documentation
└── /hardware               # Wiring diagrams, component references
