# Arduino-Morse-Code-Signal-Simulator

An Arduino Uno R3 Morse code transmitter simulator. It takes T9 multi-tap keypad input (Nokia-style), displays characters and their corresponding Morse code on a 16x4 LCD screen, and uses an LED to visually simulate antenna signal transmission.

---

## 💻 Simulation Demo

Here is the Morse code simulator in action:

![Simulation Demo](Diagrams\Demo.gif)

---

## 🛠️ Components Required

| Component | Quantity | Notes |
| :--- | :---: | :--- |
| **Arduino Uno R3** | 1 | Main microcontroller |
| **4x4 Matrix Keypad** | 1 | For T9-style alphanumeric input |
| **16x4 LCD Display** | 1 | Standard HD44780 compatible (16x2 used in Tinkercad simulation) |
| **LED** | 1 | Visual substitute for an antenna signal |
| **$220\ \Omega$ Resistors** | 2 | Current limiting for the signal LED and LCD backlight |
| **Breadboard & Jumper Wires** | 1 | For power distribution and connections |

![Components List](Diagrams\Compnents.png)

---

## 🔌 Circuit Connections

### 1. 4x4 Keypad to Arduino Uno
| Keypad Pin | Arduino Pin |
| :--- | :--- |
| **Row 1** | `D2` |
| **Row 2** | `D3` |
| **Row 3** | `D4` |
| **Row 4** | `D5` |
| **Col 1** | `D6` |
| **Col 2** | `D7` |
| **Col 3** | `D8` |
| **Col 4** | `D9` |

### 2. LCD Display to Arduino Uno
| LCD Pin | Arduino / Power Pin | Description |
| :--- | :--- | :--- |
| **VSS (GND)** | `GND` | Ground |
| **VDD (VCC)** | `5V` | Power Supply |
| **V0** | `GND` | Contrast adjustment (tied to GND for max contrast) |
| **RS** | `A0` | Register Select |
| **RW** | `GND` | Read/Write (tied to GND for Write mode) |
| **E (ENA)** | `A1` | Enable |
| **D4** | `A2` | Data Pin 4 |
| **D5** | `A3` | Data Pin 5 |
| **D6** | `A4` | Data Pin 6 |
| **D7** | `A5` | Data Pin 7 |
| **A (LED+)** | `5V` (via $220\ \Omega$ Resistor) | Backlight Anode |
| **K (LED-)** | `GND` | Backlight Cathode |

### 3. Signal LED (Antenna Simulator)
| LED Leg | Connection |
| :--- | :--- |
| **Anode (+)** | Arduino `D10` (via $220\ \Omega$ Resistor) |
| **Cathode (-)** | Arduino `GND` |

---

## 📐 Circuit Diagram & Schematics

### Breadboard Layout
![Circuit Diagram](Diagrams\Circuits%20.png)

### Schematic View
![Circuit Schematic](Diagrams\schematics.png)

---

## 📸 Real-World Build

Here is the physical prototype in action translating text into Morse code signals:

| Hardware Setup | Wiring Overview | Live Morse Transmission |
| :---: | :---: | :---: |
| ![Build Setup 1](REAL_BUILD\build_connect1.jpg) | ![Build Setup 2](REAL_BUILD\build_connect2.jpg) | ![Live Output](REAL_BUILD\build_connect3.jpg) |

---

## 🚀 How to Use
1. **Wire the Circuit:** Follow the pinout tables or the schematic diagram above.
2. **Upload the Code:** Open `sketch_nov11a.ino` in the Arduino IDE, ensure the `Keypad` and `LiquidCrystal` libraries are installed, and upload it to your Arduino Uno R3.
3. **Type & Transmit:** 
   - Use the **4x4 keypad** to type characters (press a key multiple times to cycle through letters, just like an old Nokia phone).
   - Press **`#`** to confirm and transmit the message.
   - Watch the **LCD** display the Morse code translation while the **LED** blinks the signal pulses (dots and dashes).