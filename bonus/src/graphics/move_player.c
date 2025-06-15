/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * Updates minimap player sprite position to match current player coords.
 * Centers sprite on player's minimap position.
 * 
 * @param g Game context pointer
 */
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
 * Checks if a map cell blocks player movement. Handles:
 * - Solid walls ('1', ' ')
 * - Closed doors ('D')
 * - Map boundaries
 * 
 * @param g Game context
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @return true if cell is blocking, false otherwise
 */
static bool	is_cell_blocking(t_game *g, int x, int y)
{
	char	cell;
	int		i;
	t_door	*door;

	cell = g->map->grid[y][x];
	if (x < 0 || x >= g->map->grid_cols || y < 0 || y >= g->map->grid_rows)
		return (true);
	if (cell == '1' || cell == ' ')
		return (true);
	if (cell == 'D')
	{
		i = 0;
		while (i < g->map->door_count)
		{
			door = &g->map->doors[i];
			if (door->x == x && door->y == y)
				return (door->state == CLOSED);
			i++;
		}
		return (true);
	}
	return (false);
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

	move_speed = MOVE_SPEED * fmin(delta_time, 0.1);
	has_moved = calc_new_player_pos(&new_pos, g, move_speed);
	if (has_moved)
	{
		if (!is_cell_blocking(g, (int)new_pos.x, (int)g->pos.y))
			g->pos.x = new_pos.x;
		if (!is_cell_blocking(g, (int)g->pos.x, (int)new_pos.y))
			g->pos.y = new_pos.y;
		update_minimap_player_sprite(g);
		update_minimap_dir_sprite(g);
	}
	return (has_moved);
}
