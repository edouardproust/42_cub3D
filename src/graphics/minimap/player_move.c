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
static void	update_rotation(t_game *g, double delta_time)
{
	double	rot_speed;
	double	old_dir_x;
	t_point	pos_px;

	rot_speed = ROT_SPEED * delta_time;
	if (g->key_states[KEY_LEFT])
	{
		g->player_rot -= rot_speed;
		old_dir_x = g->dir.x;
		g->dir.x = g->dir.x * cos(rot_speed) - g->dir.y * sin(rot_speed);
      	g->dir.y = old_dir_x * sin(rot_speed) + g->dir.y * cos(rot_speed);
	}
	if (g->key_states[KEY_RIGHT])
	{
		g->player_rot += rot_speed;
		old_dir_x = g->dir.x;
		g->dir.x = g->dir.x * cos(-rot_speed) - g->dir.y * sin(-rot_speed);
		g->dir.y = old_dir_x * sin(-rot_speed) + g->dir.y * cos(-rot_speed);
	}
	pos_px.x = (g->pos.x + g->dir.x) * MM_SCALE + g->minimap->instances[0].x;
	pos_px.y = (g->pos.y + g->dir.y) * MM_SCALE + g->minimap->instances[0].y;
	g->mm_dir->instances[0].x = pos_px.x - g->mm_dir->width / 2;
	g->mm_dir->instances[0].y = pos_px.y - g->mm_dir->height / 2;
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
 * Validates if a potential position is free of collisions on Y-axis
 * 
 * Checks 2 grid cells around the player (calculating a 0.3 hitbox)
 * 
 * @param g    Pointer to game structure
 * @param new_x   X position to validate
 * @param new_y   Y position to validate
 * @return true   Position is valid (no wall collisions)
 * @return false  Position would result in collision
 * TODO : Check with Ed if we want to use floor() and ceil() for more
 *        collision accuracy
 */
static bool	is_valid_move_y(t_game *g, double new_y)
{
	int		y1;
	int		y2;

	y1 = (int)(new_y - HITBOX);
	y2 = (int)(new_y + HITBOX);
	return (y1 >= 0 && y2 < g->map->grid_rows
		&& g->map->grid[y1][(int)g->pos.x] != '1'
		&& g->map->grid[y2][(int)g->pos.x] != '1');
}

/**
 * Validates if a potential position is free of collisions on X-axis
 * 
 * Checks 2 grid cells around the playe
 * 
 * @param g    Pointer to game structure
 * @param new_x   X position to validate
 * @param new_y   Y position to validate
 * @return true   Position is valid (no wall collisions)
 * @return false  Position would result in collision
 * TODO : Check with Ed if we want to use floor() and ceil() for more
 *        collision accuracy
 */
static bool	is_valid_move_x(t_game *g, double new_x)
{
	int		x1;
	int		x2;

	x1 = (int)(new_x - HITBOX);
	x2 = (int)(new_x + HITBOX);
	return (x1 >= 0 && x2 < g->map->grid_cols
		&& g->map->grid[(int)g->pos.y][x1] != '1'
		&& g->map->grid[(int)g->pos.y][x2] != '1');
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
	if (is_valid_move_x(g, new_x))
		g->pos.x = new_x;
	if (is_valid_move_y(g, new_y))
		g->pos.y = new_y;
	pos_px.x = g->pos.x * MM_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->pos.y * MM_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = pos_px.x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = pos_px.y - g->mm_player->height / 2;
}
