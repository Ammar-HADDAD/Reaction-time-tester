# Reaction Time Tester

This project is a simple Reaction Time Tester built using an Arduino and an I2C LCD display. The aim of the game is to test how quickly you can react to a visual cue (LEDs lighting up) by pressing a button as soon as all the LEDs turn off.

## Features

- **LED Sequence**: The game lights up a sequence of LEDs to signal the start of the reaction test.
- **Random Delay**: After the LED sequence, there is a randomized delay before the LEDs turn off to prevent anticipation.
- **Reaction Time Measurement**: Measures the time taken between the LEDs turning off and the button press.
- **Score Tracking**: Displays the reaction time on the LCD and tracks the best (fastest) reaction time as a record.
- **Game Over Condition**: If the button is pressed too early (before LEDs turn off), the game ends and displays a "Game Over" message.

## Online Simulation

Explore and interact with an online simulation of this project using the following link:

- [Wokwi Online Simulation](https://wokwi.com/projects/409115410917539841)

## Repository Contents

- `reaction_time_tester.ino`: The Arduino sketch file containing the game code.
- `circuit_diagram.PNG`: Circuit diagram file for the project.
- `README.md`: This file with project description and instructions.

## Components

- **Arduino Board**: The main controller for the project.
- **I2C LCD Display**: Used to display game messages and scores.
- **5 LEDs**: Light up in sequence to signal the start of the game.
- **Push Button**: Used by the player to record their reaction time.
- **Resistors and Wires**: For connecting LEDs, button, and LCD to the Arduino.

## How to Use

1. **Upload**: Upload the provided code to your Arduino board.
2. **Connect**: Connect the LEDs, button, and LCD to the Arduino as described in the code.
3. **Play**: Press the button to start the game. React as quickly as possible when the LEDs turn off.

## License

This project is currently not licensed. Feel free to use or modify it for personal or educational purposes. If you would like to add a license, consider choosing an open-source license that fits your needs.
