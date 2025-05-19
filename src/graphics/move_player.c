#include "cub3d.h"

static void	update_minimap_player_sprite(t_game *g)
{
	int	x;
	int	y;

	x = g->pos.x * MM_SCALE + g->minimap->instances[0].x;
	y = g->pos.y * MM_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = y - g->mm_player->height / 2;
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
 * @param g    Pointer to game structure
 * @param new_y   Y position to validate
 * @return true   Position is valid (no wall collisions)
 * @return false  Position would result in collision with a wall
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
 * @param g    Pointer to game structure
 * @param new_x   X position to validate
 * @return true   Position is valid (no wall collisions)
 * @return false  Position would result in collision with a wall
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
void	move_player(t_game *g, double delta_time)
{
	double	new_x;
	double	new_y;
	double	frame_speed;

	frame_speed = MOVE_SPEED * delta_time;
	calculate_new_position(g, frame_speed, &new_x, &new_y);
	if (is_valid_move_x(g, new_x))
		g->pos.x = new_x;
	if (is_valid_move_y(g, new_y))
		g->pos.y = new_y;
	update_minimap_player_sprite(g);
}
