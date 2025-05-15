#ifndef CONFIG_H
# define CONFIG_H

/* Window Settings */
# define WIDTH 			1024			/* Main window width in pixels */
# define HEIGHT			640			/* Main window height in pixels */

/* Minimap Settings */
# define MN_SCALE 		14			/* Pixels per grid cell in minimap */
# define MN_X 			14			/* X offset from left window edge */
# define MN_Y 			10			/* Y offset from top window edge */
# define MN_COLOR_GRID	0x00000000	/* Color of the grid in minimap */
# define MN_COLOR_WALL	0xFFFFF0FF	/* Color of the walls in minimap */
# define MN_COLOR_FLOOR	0x0A1D37FF	/* Color of the walls in minimap */
# define MN_COLOR_PLAYR	0xFFD700FF	/* Color of the player dot in minimap */
# define MN_COLOR_DIR	0x00FF00FF	/* Color of the player direction line in minimap */

/* Player Settings */
# define MOVE_SPEED 	5.0			/* Base movement speed (units/second) */
# define ROT_SPEED		3.0			/* Rotation speed (radians/second)*/
# define HITBOX 		0.3			/* Collision buf around player (0.3=30% cell) */
# define PLAYER_RADIUS 	5			/* Visual radius of player in minimap pixels */

/* Keyboard Settings */
typedef enum e_keys
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ESC,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_COUNT
}	t_keys;

#endif
