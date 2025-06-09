#include "cub3d.h"

void	update_minimap_dir_sprite(t_game *g)
{
	int	x;
	int	y;

	x = (g->pos.x + g->dir.x) * MM_SCALE + g->minimap->instances[0].x;
	y = (g->pos.y + g->dir.y) * MM_SCALE + g->minimap->instances[0].y;
	g->mm_dir->instances[0].x = x - g->mm_dir->width / 2;
	g->mm_dir->instances[0].y = y - g->mm_dir->height / 2;
}

static bool	update_vectors_on_rotate(t_game *g, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->dir.x;
	g->dir.x = g->dir.x * cos(rot_speed) - g->dir.y * sin(rot_speed);
	g->dir.y = old_dir_x * sin(rot_speed) + g->dir.y * cos(rot_speed);
	old_plane_x = g->cam_plane.x;
	g->cam_plane.x
		= g->cam_plane.x * cos(rot_speed) - g->cam_plane.y * sin(rot_speed);
	g->cam_plane.y
		= old_plane_x * sin(rot_speed) + g->cam_plane.y * cos(rot_speed);
	return (true);
}

/**
 * Updates the player's rotation angle based on left/right key presses.
 *
 * @param g Pointer to the game structure.
 * @param delta_time Time since the last frame (for smooth movement).
 *
 * 1. Calculates rotation speed scaled by delta_time.
 * 2. Adjusts player_rot angle using ROT_SPEED (radians per second).
 * 3. Update values of g->dir and g->cam_plane
 * 4. Update direction dot image location oin window
 *
 * - Left arrow: Decreases angle (counter-clockwise).
 * - Right arrow: Increases angle (clockwise).
 * @return bool true is player has moved, false otherwise.
 */
bool	rotate_player(t_game *g, double delta_time)
{
	bool	has_moved;

	has_moved = false;
	if (g->key_states[KEY_RIGHT])
		has_moved = update_vectors_on_rotate(g, ROT_SPEED * delta_time);
	if (g->key_states[KEY_LEFT])
		has_moved = update_vectors_on_rotate(g, -ROT_SPEED * delta_time);
	if (has_moved)
		update_minimap_dir_sprite(g);
	return (has_moved);
}
