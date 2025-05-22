#include "cub3d.h"

/**
 * Calculate the players's new position on the grid on key pressed UP,
 * DOWN, LEFT or RIGHT.
 * @return bool true if player has moved, false otherwise
 */
static bool	calc_new_player_pos(t_point	*new_pos, t_game *g, double move_speed)
{
	new_pos->x = g->pos.x;
	new_pos->y = g->pos.y;
	if (g->key_states[KEY_W] || g->key_states[KEY_UP])
	{
		new_pos->x = g->pos.x + g->dir.x * move_speed;
		new_pos->y = g->pos.y + g->dir.y * move_speed;
	}
	if (g->key_states[KEY_S] || g->key_states[KEY_DOWN])
	{
		new_pos->x = g->pos.x - g->dir.x * move_speed;
		new_pos->y = g->pos.y - g->dir.y * move_speed;
	}
	if (g->key_states[KEY_A])
	{
		new_pos->x = g->pos.x + g->dir.y * move_speed;
		new_pos->y = g->pos.y - g->dir.x * move_speed;
	}
	if (g->key_states[KEY_D])
	{
		new_pos->x = g->pos.x - g->dir.y * move_speed;
		new_pos->y = g->pos.y + g->dir.x * move_speed;
	}
	return ((new_pos->x != g->pos.x) || (new_pos->y != g->pos.y));
}

void	update_minimap_player_sprite(t_game *g)
{
	int	x;
	int	y;

	x = g->pos.x * MM_SCALE + g->minimap->instances[0].x;
	y = g->pos.y * MM_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = y - g->mm_player->height / 2;
}

/**
 * Move player if keys UP, DOWN< LEFT or RIGHT is pressed.
 *
 * @return bool true if has moved, false otherwise.
 * @note Cap on delta_time to 100ms, to prevnet jumps of the player
 * out limits
 */
bool	move_player(t_game *g, double delta_time)
{
	double	move_speed;
	t_point	new_pos;
	bool	has_moved;
	char	cell_char;

	move_speed = MOVE_SPEED * fmin(delta_time, 0.1);;
	has_moved = calc_new_player_pos(&new_pos, g, move_speed);
	if (has_moved)
	{
		cell_char = g->map->grid[(int)g->pos.y][(int)new_pos.x];
		if (new_pos.x > 0 && new_pos.x < g->map->grid_cols
			&& cell_char != '1' && cell_char != ' ')
			g->pos.x = new_pos.x;
		cell_char = g->map->grid[(int)new_pos.y][(int)g->pos.x];
		if (new_pos.y > 0 && new_pos.y < g->map->grid_rows
			&& cell_char != '1' && cell_char != ' ')
			g->pos.y = new_pos.y;
		update_minimap_player_sprite(g);
		update_minimap_dir_sprite(g);
	}
	return (has_moved);
}
