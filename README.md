# gimbal-rc-interface

📡 Project: External Pulse-Based Angle Decoder for STM32G0
This firmware is designed to interface with external systems—such as flight controllers (e.g., Pixhawk) or any device capable of generating PWM signals—and convert incoming pulse widths into angular values.

Upon receiving a PWM input signal (typically 1000–2000 µs), the system interprets the pulse width and maps it to a corresponding angle in degrees. This mechanism enables real-time control or feedback interpretation for applications such as:

Gimbal positioning

RC input signal decoding

Motion control synchronization

Angle feedback for stabilization systems

🔧 Key Features:
Captures external PWM input via STM32 hardware timers

Converts pulse width into angle range (e.g., 0–180° or customizable)

Compatible with signals from Pixhawk or RC receivers

Lightweight and real-time performance using interrupt or input capture mode

Note:
This code is designed as a one-way decoder—it does not control motors but strictly interprets incoming signals.
You may integrate it with your existing gimbal or control system to provide external manual or autonomous control input via PWM.
