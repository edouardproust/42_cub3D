/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/**
 * Advances raycasting along X-axis (vertical hit detection).
 * Updates ray state and sets cardinal direction.
 * 
 * @param ray Current raycasting context
 */
static void	advance_ray_x(t_ray *ray)
{
	ray->length_x += ray->len_step_x;
	ray->cell.x += ray->cell_move.x;
	ray->is_vertical_hit = true;
	if (ray->dir.x > 0)
		ray->side = EA;
	else
		ray->side = WE;
}

/**
 * Advances raycasting along Y-axis (horizontal hit detection).
 * Updates ray state and sets cardinal direction.
 * 
 * @param ray Current raycasting context
 */
static void	advance_ray_y(t_ray *ray)
{
	ray->length_y += ray->len_step_y;
	ray->cell.y += ray->cell_move.y;
	ray->is_vertical_hit = false;
	if (ray->dir.y > 0)
		ray->side = SO;
	else
		ray->side = NO;
}

/**
 * Processes door hits during raycasting. Marks ray as:
 * - Wall hit if door is closed
 * - Door hit for special rendering
 * 
 * @param ray Current raycasting context
 * @param g Game context
 * @return true if hit closed door, false otherwise
 */
static bool	ray_cast_on_door(t_ray *ray, t_game *g)
{
	t_door	*door;

	door = get_door_pos(g->map, ray->cell.x, ray->cell.y);
	if (!door || door->state == OPEN)
		return (false);
	if (door->state == CLOSED)
	{
		ray->wall_hit = true;
		ray->door_hit = true;
		return (true);
	}
	return (false);
}

/**
 * Executes DDA (Digital Differential Analysis) algorithm:
 * - Steps through grid until hitting wall/door
 * - Tracks hit direction and position
 * - Handles special door cases
 * 
 * @param ray Raycasting context
 * @param g Game context
 */
void	perform_dda_algorythm(t_ray *ray, t_game *g)
{
	ray->wall_hit = false;
	ray->door_hit = false;
	while (!ray->wall_hit)
	{
		if (ray->length_x < ray->length_y)
			advance_ray_x(ray);
		else
			advance_ray_y(ray);
		if (g->map->grid[ray->cell.y][ray->cell.x] == '1')
			ray->wall_hit = true;
		else if (g->map->grid[ray->cell.y][ray->cell.x] == 'D')
			ray_cast_on_door(ray, g);
	}
}
