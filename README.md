<h1>Bluetooth-Enabled Analog Alarm Clock with Arduino HC-05 Integration</h1>

### Description

This project transforms an [analog alarm clock](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Clock_size.jpg) into a smart device that can be controlled via bluetooth with a smartphone. By integrating an Arduino HC-05 Bluetooth module, a small DC motor, and a custom smartphone app, this project allows the alarm clock's bells to ring upon receiving an external Bluetooth signal.

This project was created in response to a request for a [theatre play](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Theatre_play.JPG), where an existing analog clock needed to be controlled to ring at a specific time during the performance.

<h2>Components:</h2>

Below you can see a diagram of the full circuit with its main components:

<p align="center">
  <img src="https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Circuit.png" alt="Circuit">
  <br>
  <i>Full circuit diagram (main components).</i>
</p>

In this diagram, we can see the following components:

- Arduino (can be a [Mega](https://docs.arduino.cc/resources/datasheets/A000067-datasheet.pdf), [UNO](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf) or [NANO](https://docs.arduino.cc/resources/datasheets/A000005-datasheet.pdf))

- [HC-05 Bluetooth module](https://www.ptrobotics.com/modulos-bluetooth/4364-modulo-bluetooth-hc-05-para-arduino.html)

- [5V DC motor](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Motor_and_switch.jpeg)

- [1N4148 Diode](https://www.mouser.es/ProductDetail/onsemi-Fairchild/1N4148?qs=i4Fj9T%2FoRm8RMUhj5DeFQg%3D%3D)

- [IRLZ44NPBF N-Channel MOSFET](https://www.mouser.es/ProductDetail/Infineon-Technologies/IRLZ44NPBF?qs=9%252BKlkBgLFf15OZZk%252BD0ibg%3D%3D)

- [Four 1.5V AA Batteries](https://www.nkon.nl/en/4-aa-varta-longlife-in-blister.html)

- [DPDT Sliding Switch](https://es.farnell.com/multicomp-pro/slide-switch-miniature-dpco/interrup-dpdt-0-5a-50vcc-panel/dp/599293)

I have used an [Arduino Mega](https://docs.arduino.cc/resources/datasheets/A000067-datasheet.pdf) for the prototype, but the final assembly for project uses an [Arduino NANO](https://docs.arduino.cc/resources/datasheets/A000005-datasheet.pdf) - since it was the only Arduino that could be discretely attached to the clock. Below is a step-by-step overview of how the circuit is assembled and why the components above are used.

#### Arduino
- Main Controller for the project.
- Digital pins handle input/output signals for the HC-05 and motor control.
- Powered via the four 1.5V AA batteries
  - *Note #1: I used four 1.5V AA batteries to power the Arduino through its 5V pin. This **not** ideal, since their combined voltage matches the absolute maximum voltage rating of 6V of the microcontroller (and exceeds the recommended 5.5V limit); however, I proceeded like this due to the urgency of this project and also used batteries that were not at full capacity, totaling at around 5.5V. This could be solved by using a small-footprint 5V powerbank*.
  - *Note #2: Since the DC motor is connected directly to the four batteries, an inflated voltage (i.e., >5V) will allow its axis to spin a bit faster - in this case it was necessary, since this motor could not make the ringer mechanism ring the bells loud enough (the main point of this project, since the [clock was placed inside a closed fridge for the theatre performance](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Theatre_play.JPG))*

#### HC-05 Bluetooth Module
- **VCC** → Arduino **5V**
- **GND** → Arduino **GND**
- **TXD** → Arduino **RX**
- **RXD** → Arduino **TX**

<!-- parei aqui -->

#### 5V DC Motor
- Powered by the **4×1.5V AA batteries** (~6V total).
- **Positive motor terminal** → Battery pack’s **positive**.
- **Negative motor terminal** → **Drain** of the MOSFET (allows switching).

#### IRLZ44NPBF N-Channel MOSFET
- **Gate**: Connects to an Arduino **digital pin** (e.g., pin 10) (optionally through a resistor).
- **Drain**: Connects to the **negative terminal** of the motor.
- **Source**: Connects to **common ground** (Arduino GND and battery negative).
- **Logic-Level MOSFET**:
  - Fully switches ON at **5V** gate drive.
  - Low **Rds_on** reduces heat and power loss.
  - Handles **motor current** efficiently.

#### 1N4148 Diode (Flyback Diode)
- Placed **across the motor terminals**:
  - **Cathode** (striped end) → **Positive motor terminal** (battery positive).
  - **Anode** → **Negative motor terminal** (MOSFET drain).
- **Purpose**: Protects the MOSFET from **voltage spikes** (back EMF) when the motor turns off.
  - Provides a **safe path** for the inductive current until energy is dissipated.

#### Common Ground Reference
- **Arduino GND**, **battery negative**, and **MOSFET source** must be **tied together**.
- Ensures a **consistent voltage reference** across all components.

#### How It All Works
1. **Bluetooth Connection**: The HC-05 receives signals (e.g., commands from a mobile app).
2. **Arduino Logic**: The Arduino interprets these signals and controls the MOSFET gate.
3. **Motor Control**:
   - **Gate HIGH** → MOSFET conducts → Motor runs on ~6V.
   - **Gate LOW** → MOSFET off → Motor stops.
4. **Flyback Diode**: Clamps high-voltage spikes from the motor, protecting the MOSFET.

By combining the **HC-05** module for wireless control, the **IRLZ44NPBF** MOSFET for reliable switching, and the **1N4148** diode for protection, this setup enables **safe and efficient motor control** via Bluetooth signals from the Arduino.










- [Custom smartphone app](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/GUI.png)

<h2>Custom Smartphone App:</h2>

Since this project uses an HC-05 module, there must be a way to send bluetooth signals to it. For that, a **Bluetooth-controlled application** was built using the block programming feature on the [MIT App Inventor](https://appinventor.mit.edu/), which communicates with the **Arduino via an HC-05 Bluetooth module**. The application sends a **binary signal (1 or 0)** to control the **DC motor** connected to the Arduino.

### How It Works

### 1️⃣ Connecting to a Bluetooth Device
- **`ListPicker1.BeforePicking` event:**
  - When the user taps `ListPicker1`, it retrieves the available Bluetooth devices nearby.
  - `ListPicker1.Elements` is set to `BluetoothClient1.AddressesAndNames`, listing paired devices.

- **`ListPicker1.AfterPicking` event:**
  - After selecting a Bluetooth device, the app attempts to connect via `BluetoothClient1.Connect(ListPicker1.Selection)`.
  - If successful, `ListPicker1.Text` updates to **"Connected"** (you can be this state on the grey button on top of the app's GUI, by the end of the [prototype test video](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Final_prototype_test.mp4)).

### 2️⃣ Sending Commands via Bluetooth
- **Button 1 Click (ON Command)**
  - Pressing `Button1` sends the text **"1"** using `BluetoothClient1.SendText("1")`.
  - The **HC-05 module** forwards this to the **Arduino**, which turns the **motor ON** (sets digital PWM pin ~10 to a HIGH value using the `analogWrite()` function).

- **Button 2 Click (OFF Command)**
  - Pressing `Button2` sends the text **"0"** using `BluetoothClient1.SendText("0")`.
  - The **HC-05 module** forwards this to the **Arduino**, which turns the **motor OFF** (sets digital PWM pin ~10 to a LOW value using the `analogWrite()` function).


## Usage
1. Upload the Arduino sketch (`bluetooth_arduino.ino`) to the Arduino.
2. Install `bluetooth_clock.apk` on an Android device.
3. Pair the mobile phone with the **HC-05 module**.
4. Press **Button 1** to turn the **motor ON**.
5. Press **Button 2** to turn the **motor OFF**.


## 🤝 Contributing
Feel free to submit **issues** or **pull requests** to improve this project!
