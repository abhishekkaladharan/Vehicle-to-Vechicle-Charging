# 🚗 Vehicle-to-Vehicle (V2V) Energy Transfer System using Dual Active Bridge (DAB)

## 📌 Overview

This project presents a **Vehicle-to-Vehicle (V2V) Energy Transfer System** using a **Dual Active Bridge (DAB) Converter** for intelligent bidirectional power transfer between electric vehicles (EVs). The system enables one EV with higher battery charge to transfer energy wirelessly or through a connected DC link to another EV with lower charge.

The project integrates:

- ⚡ Dual Active Bridge (DAB) Converter
- 🔋 Battery Voltage Monitoring
- 🔄 Bidirectional Power Flow
- 🧠 Embedded Control using ESP32
- 📟 LCD Monitoring System
- ⚙️ Relay-Based Protection & Isolation
- 🔥 High Frequency MOSFET Switching
- 📡 Vehicle-to-Vehicle Energy Sharing Concept

The converter uses **high-frequency transformer isolation** and **phase-controlled bridge switching** to achieve efficient and safe energy transfer between batteries.

---

# 🎯 Objectives

- Develop a smart V2V charging system
- Enable bidirectional battery energy transfer
- Implement high-frequency DAB switching
- Monitor battery voltage and SOC in real time
- Improve EV emergency charging capability
- Demonstrate intelligent power sharing between vehicles

---

# 🧠 Working Principle

The system continuously monitors the voltage of two battery packs.

### Operation Logic

- If Battery A voltage > Battery B voltage:
  - Power transfers from A → B

- If Battery B voltage > Battery A voltage:
  - Power transfers from B → A

- If both voltages are balanced:
  - Converter stops switching

The ESP32 controls the MOSFET bridges using complementary PWM signals with deadtime protection to avoid shoot-through conditions.

---

# ⚡ Dual Active Bridge (DAB) Converter

## 📖 Introduction

The Dual Active Bridge converter is an isolated bidirectional DC-DC converter widely used in:

- Electric Vehicles
- Fast Charging Stations
- Battery Energy Storage Systems
- Renewable Energy Systems
- Smart Grid Applications

The DAB converter consists of:

- Two Full Bridges
- High Frequency Transformer
- High Frequency Switching Control

---

# 🔄 DAB Operating Principle

The converter transfers power using:

- High-frequency AC conversion
- Transformer isolation
- Phase shift control between bridges

Power flow direction depends on the phase relationship between the bridges.

---

# 🏗️ System Architecture

```text
        Vehicle A Battery
                │
        ┌───────▼───────┐
        │ Full Bridge A │
        └───────▲───────┘
                │
        High Frequency
          Transformer
                │
        ┌───────▼───────┐
        │ Full Bridge B │
        └───────▲───────┘
                │
        Vehicle B Battery
```

---

# 🧰 Hardware Components

| Component | Description |
|---|---|
| ESP32 | Main Controller |
| TLP350 | MOSFET Gate Driver |
| IRF640 / MOSFET | Power Switching |
| High Frequency Transformer | Isolation & Power Transfer |
| Relay Module | Battery Isolation |
| LCD I2C Display | Voltage Monitoring |
| Voltage Divider Circuit | Battery Voltage Sensing |
| Capacitors | Ripple Filtering |
| Heat Sink | Thermal Protection |

---

# 🔌 Pin Configuration

## MOSFET Driver Pins

| Signal | ESP32 Pin |
|---|---|
| HA | GPIO 25 |
| LA | GPIO 26 |
| HB | GPIO 27 |
| LB | GPIO 14 |

---

## Relay Pins

| Relay | ESP32 Pin |
|---|---|
| Relay A | GPIO 19 |
| Relay B | GPIO 18 |

---

## Voltage Sensor Pins

| Sensor | ESP32 Pin |
|---|---|
| Battery A Voltage | GPIO 34 |
| Battery B Voltage | GPIO 35 |

---

# 🖥️ Features

✅ Bidirectional charging  
✅ Automatic voltage comparison  
✅ LCD monitoring system  
✅ High-frequency switching  
✅ Relay isolation protection  
✅ Deadtime protection  
✅ Battery balancing  
✅ Automatic direction control  
✅ Real-time SOC estimation  
✅ Transformer isolated power transfer  

---

# ⚙️ Software Features

- Continuous voltage monitoring
- Automatic charging direction selection
- Complementary MOSFET switching
- Deadtime insertion
- Battery balancing logic
- LCD status display
- State machine based control

---

# 🔄 System Modes

## 1️⃣ WAIT MODE

- Both relays OFF
- System initialization
- Voltage stabilization

---

## 2️⃣ CHECK MODE

- Battery voltages measured
- Voltage difference calculation
- Charging direction determination

---

## 3️⃣ CHARGE MODE

- Relays ON
- DAB switching active
- Energy transfer begins

---

# 📟 LCD Display Parameters

The LCD displays:

- Battery A Voltage
- Battery B Voltage
- State of Charge (SOC)
- System Mode
- Power Transfer Direction

---

# 🔥 Switching Parameters

| Parameter | Value |
|---|---|
| Switching Frequency | 20 kHz |
| Deadtime | 2 µs |
| PWM Type | Complementary |
| Converter Type | Bidirectional DAB |

---

# 🛡️ Protection Features

- Over-voltage protection
- Low-voltage protection
- Relay isolation
- Deadtime shoot-through protection
- Transformer isolation
- MOSFET thermal safety

---

# 📈 Advantages

- Fast energy transfer
- Bidirectional charging
- High efficiency
- Electrical isolation
- Reduced charging dependency
- Smart EV energy sharing
- Scalable architecture

---

# 🚘 Applications

- Emergency EV charging
- Smart EV ecosystem
- Battery balancing systems
- DC microgrids
- Renewable energy storage
- Vehicle energy sharing
- Smart transportation systems

---

# 🔬 Future Improvements

- Phase-shift PWM control
- Closed-loop current control
- CAN communication
- Wireless V2V communication
- IoT monitoring
- AI-based charging optimization
- SiC MOSFET integration
- Higher efficiency transformer design

---

# 📊 Project Flow

```text
Start
   │
   ▼
WAIT MODE
   │
   ▼
CHECK BATTERY VOLTAGE
   │
   ▼
COMPARE VOLTAGES
   │
 ┌─┴───────────────┐
 │                 │
 ▼                 ▼
A > B           B > A
 │                 │
 ▼                 ▼
A → B            B → A
CHARGING         CHARGING
 │                 │
 └──────┬──────────┘
        ▼
BALANCED
        │
        ▼
STOP
```

---

# 🧪 Testing Results

- Stable 20 kHz switching achieved
- Successful bidirectional power transfer
- Real-time voltage monitoring validated
- Relay protection working correctly
- Deadtime switching verified
- Transformer isolation successful

---

# 📚 Technologies Used

- Embedded Systems
- Power Electronics
- ESP32 Programming
- High Frequency Switching
- DC-DC Converter Design
- Battery Management
- Vehicle Energy Systems

---

# 👨‍💻 Developed By

**Abhishek Kaladharan**  
Embedded & Power Electronics Engineer

---

# 📜 License

This project is developed for educational and research purposes.

---

# ⭐ GitHub Repository

If you found this project useful, give it a ⭐ on GitHub.

---
