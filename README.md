<h1>Bluetooth-Enabled Analog Alarm Clock with Arduino HC-05 Integration</h1>

### Description

This project transforms an [analog alarm clock](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Clock_size.jpg) into a smart device that can be controlled via bluetooth with a smartphone. By integrating an [Arduino HC-05 Bluetooth module](https://www.ptrobotics.com/modulos-bluetooth/4364-modulo-bluetooth-hc-05-para-arduino.html), a [small DC motor](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/Assembly%20and%20Tests/Motor_and_switch.jpeg), and a [custom smartphone app](https://github.com/danielftsilva/HC-05-Analog-Clock/blob/main/GUI.png), this project allows the alarm clock's bells to ring upon receiving an external Bluetooth signal.

This project was done 


<h2>Components:</h2>

- Analog alarm clock with bells

- Arduino (can be a Mega, UNO, NANO)

- HC-05 Bluetooth module

- Small DC motor

- Custom smartphone app

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
  - The **HC-05 module** forwards this to the **Arduino**, which turns the **motor ON** (digital pin 10 HIGH).

- **Button 2 Click (OFF Command)**
  - Pressing `Button2` sends the text **"0"** using `BluetoothClient1.SendText("0")`.
  - The **HC-05 module** forwards this to the **Arduino**, which turns the **motor OFF** (digital pin 10 LOW).


## Usage
1. Upload the Arduino sketch (`bluetooth_arduino.ino`) to the Arduino.
2. Install `bluetooth_clock.apk` on an Android device.
3. Pair the mobile phone with the **HC-05 module**.
4. Press **Button 1** to turn the **motor ON**.
5. Press **Button 2** to turn the **motor OFF**.


## 🤝 Contributing
Feel free to submit **issues** or **pull requests** to improve this project!
