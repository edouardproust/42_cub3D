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
static void	update_rotation(t_game *game, double delta_time)
{
	double	rot_speed;

	rot_speed = ROT_SPEED * delta_time;
	if (game->key_states[KEY_LEFT])
		game->player_rot -= rot_speed;
	if (game->key_states[KEY_RIGHT])
		game->player_rot += rot_speed;
}


/**
 * Calculates potential new player position based on input keys
 * 
 * @param game      Pointer to game structure containing player state
 * @param move_speed Movement speed multiplier
 * @param new_x     Pointer to store calculated X position
 * @param new_y     Pointer to store calculated Y position
 */
static void	calculate_new_position(t_game *game, double move_speed,
	double *new_x, double *new_y)
{
	*new_x = game->pos.x;
	*new_y = game->pos.y;
	if (game->key_states[KEY_W])
		*new_y -= move_speed;
	if (game->key_states[KEY_S])
		*new_y += move_speed;
	if (game->key_states[KEY_A])
		*new_x -= move_speed;
	if (game->key_states[KEY_D])
		*new_x += move_speed;
}

/**
 * Validates if a potential position is free of collisions
 * 
 * Checks 4 grid cells around the player (calculating a 0.3 hitbox)
 * 
 * @param game    Pointer to game structure
 * @param new_x   X position to validate
 * @param new_y   Y position to validate
 * @return true   Position is valid (no wall collisions)
 * @return false  Position would result in collision
 * TODO : Check with Ed if we want to use floor() and ceil() for more
 *        collision accuracy
 */
static bool	is_valid_move(t_game *game, double new_x, double new_y)
{
	int		x1;
	int		x2;
	int		y1;
	int		y2;

	x1 = (int)(new_x - HITBOX);
	x2 = (int)(new_x + HITBOX);
	y1 = (int)(new_y - HITBOX);
	y2 = (int)(new_y + HITBOX);
	return (y1 >= 0 && y2 < game->map->grid_rows
		&& x1 >= 0 && x2 < game->map->grid_cols
		&& game->map->grid[y1][x1] != '1'
		&& game->map->grid[y1][x2] != '1'
		&& game->map->grid[y2][x1] != '1'
		&& game->map->grid[y2][x2] != '1');
}

/**
 * Updates player position based on input and collision checks
 * 
 * Process:
 * 1. Calculate potential new position from input
 * 2. Validate against map collision
 * 3. Update actual position if validation passes
 *
 * @param game       Pointer to game structure
 * @param move_speed Movement speed multiplier (delta-adjusted)
 */
void	update_movement(t_game *g, double delta_time)
{
	double	new_x;
	double	new_y;
	double	frame_speed;
	t_point	pos_px;

	update_rotation(g, delta_time);
	frame_speed = MOVE_SPEED * delta_time;
	calculate_new_position(g, frame_speed, &new_x, &new_y);
	if (is_valid_move(g, new_x, new_y))
	{
		g->pos.x = new_x;
		g->pos.y = new_y;
	}
	pos_px.x = g->pos.x * MN_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->pos.y * MN_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = pos_px.x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = pos_px.y - g->mm_player->height / 2;
}
