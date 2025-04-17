# 🤖 PathPilot: Maze Solving Bot - using ESP32 and Arduino IDE

An intelligent **Maze Solving Robot** built using **ESP32**, a **servo-mounted ultrasonic sensor**, **L293D motor driver**, and a **3-wheeled chassis**. This bot uses **PID control** to maintain optimal distance from obstacles and autonomously navigates through mazes using side scanning and decision logic.

---

## 📌 Project Overview

This project demonstrates a basic but effective autonomous maze solving robot. The robot uses a servo-mounted ultrasonic sensor to scan its surroundings, makes real-time decisions based on distance data, and navigates a path through the maze. A simple PID controller adjusts the behavior based on how far the bot is from obstacles, enabling smoother movement and better adaptability.

---

## ⚙️ Hardware Components

| Component                  | Quantity | Description                                  |
|----------------------------|----------|----------------------------------------------|
| ESP32 WROOM Dev Board      | 1        | Microcontroller for processing and control   |
| L293D Motor Driver         | 1        | Controls the two DC motors                   |
| Ultrasonic Sensor (HC-SR04)| 1        | For obstacle detection                       |
| Servo Motor (SG90)         | 1        | Rotates ultrasonic sensor for directional scan |
| DC Motors                  | 2        | Rear wheel drive                             |
| 3-Wheeled Chassis          | 1        | Base structure with caster support           |
| Jumper Wires + Breadboard  | —        | For circuit connections                      |
| Battery Pack (3.7V Li-ion) | 2        | To power motors and ESP32                    |

---

## 🔌 Wiring and Pin Configuration

### ESP32 Connections

- **Ultrasonic Sensor (HC-SR04):**
  - VCC → 5V  
  - GND → GND  
  - Trig → GPIO 18  
  - Echo → GPIO 19

- **Servo Motor:**
  - Signal → GPIO 13  
  - VCC → 5V  
  - GND → GND

- **Motor Driver (L293D):**
  - IN1 → GPIO 27  
  - IN2 → GPIO 26  
  - IN3 → GPIO 25  
  - IN4 → GPIO 33  
  - ENA/ENB → 5V (or PWM pins if speed control is desired)  
  - OUT1/OUT2 → Left Motor  
  - OUT3/OUT4 → Right Motor  
  - Motor VCC → Battery  
  - GND → Common Ground with ESP32

---

## 🧠 Working Logic

1. **Scanning:**
   - Servo rotates to **90° (center)**, **165° (left)**, and **25° (right)**.
   - Ultrasonic sensor captures average distance data from each direction.

2. **PID Control:**
   - Uses a PID controller with constants `Kp = 1.2`, `Ki = 0.01`, `Kd = 0.5`.
   - Maintains a **target distance of 40cm** from obstacles.
   - Adjusts the movement based on error between target and measured distance.

3. **Decision Making:**
   - If front is **clear (>30cm)** → move forward.
   - If **obstacle ahead**, checks left and right distances.
   - Turns to the **side with more space**.
   - If **both sides blocked**, performs a fixed right turn (dead-end handling).

---

## 🧾 Features

✅ Real-time ultrasonic scanning  
✅ PID-based obstacle distance regulation  
✅ Automatic side checking using servo sweep  
✅ Smooth maze navigation with intelligent decision making  
✅ Simple and efficient pathfinding without line-following sensors

---

## 🛠️ Code Snippet (Core Loop Logic)

```cpp
if (center > 30) {
  moveForward();
} else {
  stopMoving();
  scanSides();
  if (left > right) {
    turnLeft();
  } else {
    turnRight(); // Dead end or right preferred
  }
}
```
---

## 🛠 Setup & Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/achyuth-2308/PathPilot-Maze-Solving-Bot.git
   ```
2. Open the code in **Arduino IDE** or **PlatformIO**.
3. Install the required libraries:
   - `ESP32Servo`
4. Select board: ESP32 Dev Module
5. Connect your ESP32, choose the correct port, and upload the code.
6. Upload the code to ESP32 and power up the bot!

---


## 🤝 Contributions
Feel free to fork, enhance, and create pull requests! Contributions are always welcome.

---

## 📝 License
This project is **open-source** under the MIT License.

---

### 📧 Contact
For any queries, reach out to me on **[LinkedIn](https://www.linkedin.com/in/achyuth-mukund)** or via email at **achyuth2004@gmail.com**.
