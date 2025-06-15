/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
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

	move_speed = MOVE_SPEED * fmin(delta_time, 0.1);
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
	}
	return (has_moved);
}
