#ifndef CONFIG_H
# define CONFIG_H

/* Window Settings */
# define WIDTH 			1024			/* Main window width in pixels */
# define HEIGHT			640			/* Main window height in pixels */

/* Minimap Settings */
# define MM_SCALE 		14			/* Pixels per grid cell in minimap */
# define MM_X 			14			/* X offset from left window edge */
# define MM_Y 			10			/* Y offset from top window edge */
# define MM_COLOR_GRID	0x00000000	/* Color of the grid in minimap */
# define MM_COLOR_WALL	0xFFFFF0FF	/* Color of the walls in minimap */
# define MM_COLOR_FLOOR	0x0A1D37FF	/* Color of the walls in minimap */
# define MM_COLOR_PLAYR	0xFFD700FF	/* Color of the player dot in minimap */
# define MM_COLOR_DIR	0x00FF00FF	/* Color of the player direction line in minimap */

/* Player Settings */
# define MOVE_SPEED 	5.0			/* Base movement speed (units/second) */
# define ROT_SPEED		3.0			/* Rotation speed (radians/second)*/
# define HITBOX 		0.1			/* Collision buf around player t_point (0.3=30% cell) */
# define MM_TX_PLAYER	"assets/minimap/player.png"
# define MM_PLAYER_W	14

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
