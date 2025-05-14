#include "cub3d.h"
/**
 * Updates the player's rotation angle based on left/right key presses.
 * 
 * @param game         Pointer to the game structure.
 * @param delta_time   Time since the last frame (for smooth movement).
 * 
 * 1. Calculates rotation speed scaled by delta_time.
 * 2. Adjusts player_rot angle using ROT_SPEED (radians per second).
 * 
 * - Left arrow: Decreases angle (counter-clockwise).
 * - Right arrow: Increases angle (clockwise).
 */
void	update_rotation(t_game *game, double delta_time)
{
	double	rot_speed;

	rot_speed = ROT_SPEED * delta_time;
	if (game->key_states[KEY_LEFT])
		game->player_rot -= rot_speed;
	if (game->key_states[KEY_RIGHT])
		game->player_rot += rot_speed;
}
