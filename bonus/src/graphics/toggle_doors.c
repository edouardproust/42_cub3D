/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/**
 * Attempts to toggle a door's state if player is adjacent.
 * 
 * @param door Door to toggle
 * @param px Player grid X
 * @param py Player grid Y
 * @return true if door was toggled, false otherwise
 */
static bool	try_toggle_door(t_door *door, int px, int py)
{
	if (abs(door->x - px) > 1 || abs(door->y - py) > 1)
		return (false);
	if (door->state == OPEN && door->x == px && door->y == py)
		return (false);
	door->state = !door->state;
	return (true);
}

/**
 * Toggles all doors adjacent to player position.
 * 
 * @param g Game context
 * @param player_x Player grid X
 * @param player_y Player grid Y
 * @return true if any door was toggled, false otherwise
 */
static bool	toggle_all_adjacent_doors(t_game *g, int player_x, int player_y)
{
	int		i;
	bool	toggled_any;

	i = 0;
	toggled_any = false;
	while (i < g->map->door_count)
	{
		if (try_toggle_door(&g->map->doors[i], player_x, player_y))
		{
			draw_minimap_door_cell(g, g->map->doors[i].x, g->map->doors[i].y);
			toggled_any = true;
		}
		i++;
	}
	return (toggled_any);
}

/**
 * Door interaction handler:
 * - Prevents rapid toggling with cooldown
 * - Toggles adjacent doors
 * - Forces redraw if doors changed
 * 
 * @param g Game context
 */
void	toggle_doors(t_game *g)
{
	static double	last_toggle = 0;
	double			current_time;
	int				player_x;
	int				player_y;
	bool			toggled_any;

	current_time = mlx_get_time();
	player_x = (int)g->pos.x;
	player_y = (int)g->pos.y;
	if (current_time - last_toggle < 0.3)
		return ;
	toggled_any = toggle_all_adjacent_doors(g, player_x, player_y);
	if (toggled_any)
	{
		last_toggle = current_time;
		g->force_redraw = true;
	}
}
