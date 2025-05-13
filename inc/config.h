#ifndef CONFIG_H
# define CONFIG_H

/* Window Configuration */
# define WIDTH 			800		/* Main window width in pixels */
# define HEIGHT			600		/* Main window height in pixels */

/* Minimap Configuration */
# define MN_SCALE 		20		/* Pixels per grid cell in minimap */
# define MN_X 			10		/* X offset from left window edge */
# define MN_Y 			10		/* Y offset from top window edge */

/* Player Configuration */
# define MOVE_SPEED 	5.0		/* Base movement speed in world units/second */
# define HITBOX 		0.3		/* Collision buf around player (0.3=30% cell) */
# define PLAYER_RADIUS 	3		/* Visual radius of player in minimap pixels */

#endif