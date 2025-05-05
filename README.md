# Cub3D (42 Barcelona)

**Cub3D is a 3D graphical project based on the principles of raycasting, inspired by early FPS games like Wolfenstein 3D. The goal is to build a simple 3D game engine from scratch using C and a minimal graphics library (MiniLibX).**

- **Subject:** [English](subject/en.subject.pdf) / [French](subject/fr.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** June 2025
- **Team:** [Skoteini-42](https://github.com/Skoteini-42), [edouardproust](https://github.com/edouardproust)

![Cub3D 42 Barcelona](test/screenshots/cub3d-42-demo.gif "Cub3D project at 42 school in Barcelona using minilibX")

## How to Use

### Requirements

- Unix-based system (Linux or macOS)
- gcc or clang
- make
- MiniLibX (included or installed via system package)
- X11 libraries (Linux) or an appropriate graphics environment (macOS)

### Installation

1. Install dependencies (`make`, `gcc`, `libx11-dev`, `libxext-dev` and `libbsd-dev`):
	```
	sudo apt update && sudo apt install -y make gcc libx11-dev libxext-dev libbsd-dev
	```
2. Clone the repository:
	```bash
	git clone https://github.com/your-username/cub3d.git
	cd cub3d
	```
2. Compile the project:
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

### Use compatible maps

The `.cub` map file must follow the format specified in the [subject PDF](subject/en.subject.pdf) (pages 8 to 10).

Here is an example of a compatible map:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0 

        111111111111111111111
        100000000011000000001
        100100000000000000001
11111111101100000111000000001
10000000001100000111011111111
1111011111111101110000001
1100000011010101110010001
100000000000000011001000111
110000011101010111011110N01
11111111 1111111 1111111111
```

- `F` defines the color of the floor
- `C` defines the color of the ceiling
- In the map, `N`, `S`, `W` or `E` indicate the location of the player and the corresponding direction of the point of view.

## Constraints

### Allowed functions:

- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, `gettimeofday`.
- All functions of `libft` (the library developped by students along the 42 cursus)
- All functions of the math library (link with `-lm`, see the list of functions [here](https://linux.die.net/man/3/math)).
- All functions of the MinilibX library.

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


