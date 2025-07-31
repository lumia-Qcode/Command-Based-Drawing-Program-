# Turtle Graphics with SFML

This is a **command-driven drawing application** implemented in **C++ using SFML (Simple and Fast Multimedia Library)**. This program lets users enter commands to control a cursor (turtle) and draw shapes like lines and circles.

---

## Features

- Command-based drawing (like `fd`, `bk`, `lt`, `rt`, etc.)
- Pen up/down support
- Adjustable line **thickness** and **color**
- Draw **circles** at the cursor position
- Supports `repeat [...]` loops for repeating command blocks
- Save and load command history to/from a file
- Real-time rendering using **SFML**
- Displays recent commands on the screen
- Basic error feedback for invalid commands

---

## Commands Reference

| Command         | Description                                           |
|----------------|-------------------------------------------------------|
| `fd <n>`        | Move forward `n` units                               |
| `bk <n>`        | Move backward `n` units                              |
| `lt <deg>`      | Turn left by `deg` degrees (multiple of 30 or 45)    |
| `rt <deg>`      | Turn right by `deg` degrees                          |
| `circle <r>`    | Draw a circle of radius `r`                          |
| `color <name>`  | Change pen color (see supported colors)              |
| `width <n>`     | Set line thickness (1–3)                             |
| `pu`            | Pen up (no drawing while moving)                     |
| `pd`            | Pen down (enable drawing while moving)              |
| `cs`            | Clear screen (reset canvas)                          |
| `save <file>`   | Save command history to file                         |
| `load <file>`   | Load and execute command history from file           |
| `repeat n [ ... ]` | Repeat the enclosed commands `n` times          |

---

## Supported Colors

- `red`
- `blue`
- `green`
- `yellow`
- `purple`
- `orange`
- `pink`
- `brown`
- `white`
- `gray`

---

## How to Build and Run

### Requirements:
- C++ Compiler (e.g., g++)
- [SFML Library](https://www.sfml-dev.org/) (2.x)

### On Windows (using g++ and SFML):
1. **Install SFML**
   - Download from https://www.sfml-dev.org/download.php
   - Set up SFML include and lib paths in your compiler

2. **Build Command**
   ```bash
   g++ main.cpp -o turtle_app -lsfml-graphics -lsfml-window -lsfml-system

## Author
Lumia Noman Qureshi<br>
BSCS Student<br>
FAST NUCES
