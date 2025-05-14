# Cub3D (42 Barcelona)

**Cub3D is a 3D graphical project based on the principles of raycasting, inspired by early FPS games like Wolfenstein 3D. The goal is to build a simple 3D game engine from scratch using C and a minimal graphics library (MiniLibX).**

- **Subject:** [English](subject/en.subject.pdf) / [French](subject/fr.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** June 2025
- **Team:** [Skoteini-42](https://github.com/Skoteini-42), [edouardproust](https://github.com/edouardproust)

![Cub3D 42 Barcelona](test/screenshots/cub3d-42-demo.gif "Cub3D project at 42 school in Barcelona using mlx42")

## How to Use

### Installation

1. #### Install dependencies

	Cub3D relies on library [MLX42](https://github.com/codam-coding-college/MLX42) for the 3D rendering aspect. MLX42 is using [GLFW](https://www.glfw.org/) for window and input handling, and [CMake](https://cmake.org/) for the build process.

	**On Linux (Debian/Ubuntu):**
	```
	sudo apt update && sudo apt install -y make gcc cmake libglfw3-dev libdl-dev libpthread-stubs0-dev
	```

	**On macOS (using Homebrew):**
	```
	brew install glfw cmake
	```

2. #### Clone the repository:

	```bash
	git clone https://github.com/your-username/cub3d.git
	cd cub3d
	```

3. #### Compile the project:

	```
	make
	```

### Running the Program

Once compiled, launch the program with a map file:
```
./cub3D assets/maps/example.cub
```

### Controls

- `W`, `A`, `S`, `D`: Move forward, left, backward, and right
- `←`, `→`: Rotate view left and right
- `ESC`: Exit the game

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
- All functions of the MLX42 library.

## MLX42 Library Usage

1. mlx_init : Initializes the MLX context and creates a window.

Usage:

`game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);  `

2.  mlx_new_image : Creates an image buffer for rendering. ( Used for the main screen and minimap rendering buffers.)

Usage :

```
game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);  
game->minimap = mlx_new_image(game->mlx, mm_width, mm_height);  
```
3.  mlx_image_to_window : Attaches an image to the window at specified coordinates. (Positions the main screen and minimap images on the window.)

Usage :

```
mlx_image_to_window(game->mlx, game->screen, 0, 0);  
mlx_image_to_window(game->mlx, game->minimap, MN_X, MN_Y); 
```

4. mlx_put_pixel : Draws a single pixel on an image. (Used in draw_minimap_cell, draw_player_circle, and draw_direction_line for pixel-level rendering.)

Usage :

`mlx_put_pixel(game->minimap, x, y, color);  `

5. mlx_loop : Starts the main rendering/event loop.

Usage : 

`mlx_loop(game->mlx); // In main()`

6. mlx_key_hook : Registers a "trirgger" for key press/release events. (Handles keyboard input for movement (WASD), rotation (arrow keys), and exit (ESC).)

Usage :

`mlx_key_hook(game->mlx, key_hook, game);  `

7. mlx_close_hook : Triggers window close events (e.g., clicking the X button).

Usage :

`mlx_close_hook(game->mlx, close_hook, game);  `

8. MLX_RELEASE : Determines if a key is pressed or released (e.g., continous movement while holding W).

Check key_hook() for reference in src/graphics/hooks.c

9. Closes the window when ESC is pressed.

```
if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)  
    mlx_close_window(game->mlx); 

```
10. mlx_get_time : Returns the time in seconds since MLX was initialized.

Usage : 

```
double current_time = mlx_get_time();  
double delta = current_time - game->last_frame; 
```

11. mlx_loop_hook : Registers a function to run every frame. (It's responsible for the game loop (rendering, movement, etc.).

Usage :

`mlx_loop_hook(game->mlx, render_minimap, game); `

12. mlx_close_window : Closes the MLX window.

Usage :

`mlx_close_window(game->mlx);`

13. mlx_delete_image : Removes an image from the MLX context and frees its pixel buffer memory

Usage :

```
if (g->screen)  
    mlx_delete_image(g->mlx, g->screen);  
if (g->minimap)  
    mlx_delete_image(g->mlx, g->minimap); 
```

14. mlx_terminate : Shuts down the MLX context, closes the window, and frees all remaining MLX resources.

Usage :

`mlx_terminate(g->mlx);`

## Features

### 🧱 Raycasting Engine
- Implements a basic 3D rendering engine using raycasting, similar to early FPS games like *Wolfenstein 3D*.
- Calculates wall distances and renders vertical slices based on player orientation.

### 🗺️ Custom Map Parsing
- Supports custom `.cub` map files with textures, wall layout, player start position, and more.
- Validates map integrity (closed walls, valid characters, texture paths, etc.).

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
- Uses MLX42 to handle keyboard input and window events.
- Clean event loop for rendering and game state updates.

### 🔄 Expandability
- Clear code structure designed for potential future features like:
  - Sprite rendering (enemies, items)
  - Doors or teleportation
  - Mini-map or UI elements

### 📚 Resources
- https://www.youtube.com/watch?v=gYRrGTC7GtA&list=PLCWsH9Tj9oWyDM4W43VMj5yo2PdyYMGst&ab_channel=3DSage
- https://phet.colorado.edu/sims/html/trig-tour/latest/trig-tour_all.html

