#ifndef CONFIG_H
# define CONFIG_H

/* Window Settings */
# define WIDTH 			1024	/* Main window width in pixels */
# define HEIGHT			640		/* Main window height in pixels */

/* Minimap Settings */
# define MM_SCALE 		14		/* Pixels per grid cell in minimap */
# define MM_X 			14		/* X offset from left window edge */
# define MM_Y 			10		/* Y offset from top window edge */
# define MM_COLOR_GRID	0x00000000	/* Color of the grid in minimap */
# define MM_COLOR_WALL	0xFFFFF0FF	/* Color of the walls in minimap */
# define MM_COLOR_FLOOR	0x0A1D37FF	/* Color of the walls in minimap */

/* Player Settings */
# define MOVE_SPEED 	5.0		/* Base movement speed (units/second) */
# define ROT_SPEED		3.0		/* Rotation speed (radians/second)*/
# define MM_PLAYER_IMG	"assets/minimap/player.png"
# define MM_PLAYR_WIDTH	16
# define MM_DIR_IMG		"assets/minimap/viewpoint.png"
# define MM_DIR_WIDTH	6

/* 3D Rendering Settings */
# define COLOR_MODE		true
# define FOV_FACTOR		0.66
# define FISHEYE_EFFECT	false
# define WALL_COLOR_NO	0xFF00FFFF	/* magenta */
# define WALL_COLOR_SO	0x00FFFFFF	/* cyan */
# define WALL_COLOR_EA	0xFFFF00FF	/* yellow */
# define WALL_COLOR_WE	0x00FF00FF	/* green */

/* Keyboard Settings */
typedef enum e_keys
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ESC,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_COUNT
}	t_keys;

#endif
