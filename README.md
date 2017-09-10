# Thermoelectric Cooler Fridge

## Description
Arduino code to control thermoelectric coolers wired to an H-bridge with PWM. PWM output is filtered using a LC low-pass filter to ensure an analog signal.

LC low-pass filter constructed using 100 uH inductor and 470 uF capacitor for a cutoff frequency of ~700 Hz.

## Current Functionality
- [X] Reads temperature inside fridge
- [X] Uses PID control loop to control TEC output according to difference from target temperature
- [X] Displays target temperature on LCD screen
- [X] Custom PWM output frequency of 16 kHz to ensure that PWM frequency is much above the LC low-pass filter's cutoff frequency
- [X] Outputs PWM signal to high current H-bridge

## To-do
- [ ] Adjustable target temperature while control system is running
- [ ] Tuned Kp, Ki and Kd values
- [ ] Automatic tuning
- [ ] Fix erratic temperature readings 🐞

## Changelog:
## Alpha 1.0
- Reads temperature inside fridge
- Uses PID control loop to control TEC output according to difference from target temperature
- Displays target temperature on LCD screen
- Custom PWM output frequency of 16 kHz to ensure that PWM frequency is much above the LC low-pass filter's cutoff frequency
- Outputs PWM signal to high current H-bridge
