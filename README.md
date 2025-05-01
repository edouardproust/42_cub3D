# Cube3D (42 Barcelona)

**Cube3D is a 3D graphical project based on the principles of raycasting, inspired by early FPS games like Wolfenstein 3D. The goal is to build a simple 3D game engine from scratch using C and a minimal graphics library (MiniLibX).**

- **Subject:** [English](subject/en.subject.pdf) / [French](subject/fr.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** June 2025
- **Team:** [Skoteini-42](https://github.com/Skoteini-42), [edouardproust](https://github.com/edouardproust)

![Cube3D 42 Barcelona](test/screenshots/cube3d-42-demo.gif "Cube4D project at 42 school in Barcelona using minilibX")

## Skills

This project is part of the 42 school curriculum and challenges students to implement core computer science concepts such as:

- **Low-level graphics programming:** rendering walls, sprites, and textures using raycasting techniques.
- **Mathematics and algorithms:** implementing vector math, player movement, collision detection, and field of view calculations.
- **Memory management and optimization:** writing efficient C code without memory leaks or undefined behavior.
- **Parsing and file handling:** loading and interpreting a custom map configuration from files.
- **Event handling and user interaction:** managing keyboard inputs to control the player in real-time.

Cube3D is a comprehensive exercise in systems programming and serves as an introduction to the fundamentals of game development, rendering pipelines, and engine architecture.

## How to Use

### Requirements

- Unix-based system (Linux or macOS)
- gcc or clang
- make
- MiniLibX (included or installed via system package)
- X11 libraries (Linux) or an appropriate graphics environment (macOS)

### Installation

Clone the repository:
```bash
git clone https://github.com/your-username/cube3d.git
cd cube3d
```
Compile the project:
```
make
```

### Running the Program

Once compiled, launch the program with a map file:
```
./cub3D maps/example.cub
```

### Controls

- W / A / S / D – Move forward, left, backward, and right
- ← / → – Rotate view left and right
- ESC – Exit the game

### Notes

- The .cub map file must follow the format specified in the subject PDF.
- If you encounter errors with MiniLibX, ensure that all dependencies are correctly installed on your system (e.g., libmlx, X11, Xext on Linux).

## Features

### 🧱 Raycasting Engine
- Implements a basic 3D rendering engine using raycasting, similar to early FPS games like *Wolfenstein 3D*.
- Calculates wall distances and renders vertical slices based on player orientation.

### 🗺️ Custom Map Parsing
- Supports custom `.cub` map files with textures, wall layout, player start position, and more.
- Validates map integrity (closed walls, valid characters, texture paths).

### 🎮 Real-Time Player Movement
- Smooth forward/backward/strafe movement and real-time rotation.
- Collision detection to prevent walking through walls.

### 🎨 Textures & Graphics
- Loads wall textures (N/S/E/W), floor and ceiling colors.
- Renders walls with correct perspective and texture scaling.

### 🧠 Memory & Resource Management
- Manages dynamic memory carefully (no leaks, no double frees).
- Cleans up all resources (graphics context, windows, file descriptors) on exit.

### ⚙️ Event-Driven Architecture
- Uses MiniLibX to handle keyboard input and window events.
- Clean event loop for rendering and game state updates.

### 🔄 Expandability
- Clear code structure designed for potential future features like:
  - Sprite rendering (enemies, items)
  - Doors or teleportation
  - Mini-map or UI elements


