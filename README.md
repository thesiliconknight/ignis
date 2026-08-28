# Ignis
A low-voltage controller board for driving a 220V 400W aluminum PTC heater through an external SSR, it uses a NTC for temperature sensing, an OLED status display, and MOSFET-isolated relay switching. The board is built around the CH32V006F8P6 MCU, which handles the ADC sensing, OLED interface, and SSR triggering entirely off 3.3V/5V logic, keeping all mains voltage completely off-board.
## Pictures
| Top View | Bottom View |
| :---: | :---: |
| ![Board Front](Images/topbrd.png) | ![Board Back](Images/btmbrd.png) |
## Features
* **Main Controller:** CH32V006F8P6, providing 62KB Flash and 8KB RAM, cheap, powerful and reliable
* **USB-C Power:** Board is powered entirely over USB-C.
* **No High Voltage:** The custom PCB handles 5V/3.3V logic. The 220V AC mains load is kept entirely off-board and switched safely via an external SSR.
* **Precision Sensing:** Utilizes a 100K NTC 3950 glass-bead thermistor it can read up to 300°C.
* **Robust Relay Driver:** An AO3400A logic-level N-channel MOSFET drives the external SSR, protecting the MCU's GPIO pins from current draw.
* **OLED Interface:** I2C header for a standard 0.91" SSD1306 OLED module to display target temperature, current temperature, and heating status.
* **Status LEDs:** Inbuilt HEATING and RDY LEDs gives the heater state without needing a screen.
* **Button Header:** 5-pin header breaking out 4 tactile buttons for on-device navigation.
## Components Used
* **Microcontroller:** WCH CH32V006F8P6 (TSSOP-20)
* **Power Input:** USB-C receptacle (power-only)
* **High Voltage Switch:** External SSR connected via terminal block
* **Heater:** 220V 400W PTC Aluminum Heating Plate
* **Thermistor:** 100K NTC, connected via a JST-PH 2-pin connector
* **Screen:** 0.91" SSD1306 I2C OLED Module
* **Miscellaneous:** AMS1117-3.3V Regulator, AO3400A MOSFET, 4x tactile buttons, 2x status LEDs, and assorted 0603 passives.
## Bill of Materials (BOM)
| Qty | Component | Footprint | Designator(s) |
| :---: | :--- | :--- | :--- |
| 1 | Conn_01x05_Socket (Buttons Header) | PinHeader_1x05_P2.54mm_Vertical | BTNS |
| 4 | 100nF Capacitor | C_0603_1608Metric | C1, C7, C8, C9 |
| 1 | 1µF Capacitor | C_0603_1608Metric | C2 |
| 1 | 0.1µF Capacitor | C_0603_1608Metric | C4 |
| 1 | 10µF Capacitor | C_0603_1608Metric | C5 |
| 2 | LED (Heating / Ready) | LED_0805_2012Metric | HEATING, RDY |
| 1 | USB-C Receptacle (Power Only) | USB4125-xx-x 6P TopMnt Horizontal | J6 |
| 1 | Conn_01x02_Socket (NTC) | JST_PH_S2B-PH-K_1x02_P2.00mm_Horizontal | NTC |
| 1 | Conn_01x03_Pin (Programming Header) | PinHeader_1x03_P2.54mm_Vertical | PRGRM |
| 1 | AO3400A N-Channel MOSFET | SOT-23 | Q1 |
| 2 | 5.1kΩ Resistor | R_0603_1608Metric | R3, R9 |
| 1 | 1kΩ Resistor | R_0603_1608Metric | R4 |
| 1 | 10kΩ Resistor | R_0603_1608Metric | R5 |
| 1 | 100kΩ Resistor | R_0603_1608Metric | R6 |
| 2 | 330Ω Resistor | R_0603_1608Metric | R7, R8 |
| 1 | 0.91" I2C OLED | Untitled | SCREEN |
| 1 | Conn_01x02_Socket (SSR) | TerminalBlock_Phoenix_PT-1,5-2-5.0-H_1x02_P5.00mm_Horizontal | SSR |
| 4 | SW_Push (6mm Tactile) | SW_PUSH_6mm | SW1, SW2, SW3, SW4 |
| 1 | CH32V006FxPx MCU | TSSOP-20_4.4x6.5mm_P0.65mm | U1 |
| 1 | AMS1117-3.3 LDO | SOT-223-3_TabPin2 | U3 |

| Schematic Design |
| :---: |
| ![Schematic Diagram](Images/schematics.png) |

| PCB Top Layer Routing | PCB Bottom Layer Routing |
| :---: | :---: |
| ![Top Routing](Images/routing_topbrd.png) | ![Bottom Routing](Images/routing_btmbrd.png) |
### Connections
* **Power (USB-C to 3.3V):** 5V via USB-C (J6) and routes to the SSR connector and the AMS1117 V.REG (U3), which powers the MCU, OLED, and thermistor etc.
* **Thermistor Input (NTC):** Connects the 100K NTC between 3.3V and the MCU's ADC pin (PD2).
* **SSR Driver (SSR):** The MCU's PWM pin (PC3) switches the AO3400 Gate (Q1). The MOSFET pulls the negative side of the SSR terminal to GND, triggering the external relay.
* **OLED Header (SCREEN):** Connected to PC1 (SDA) and PC2 (SCK).
* **Button Header (BTNS):** 5-pin header breaking out the 4 tactile switches (SW1–SW4).
* **Programming Header (PRGRM):** Breaks out 3.3V, GND, and the single-wire debug line (PD1 / SWIO) for the programmer.
* **Status LEDs:** HEATING and RDY LEDs (Pin PD2 & PD3)
## License
This hardware project is open-source and licensed under the CERN Open Hardware Licence Version 2 - Strongly Reciprocal (CERN-OHL-S-2.0). 
You are free to copy, modify, distribute, and manufacture this board for personal or commercial use. However, if you modify these schematic or layout files and distribute your new design, you must release those modifications under this exact same CERN-OHL-S-2.0 license.
This design is shared without any warranty or implied guarantee. Check the LICENSE file for the full legal text.
