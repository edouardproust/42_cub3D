/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Get how many pixels to draw on the screen to project the
 * wall height for the current ray.
 */
static void	set_wall_screen_boundaries(t_ray *ray, double wall_dist,
		t_game *g)
{
	int	wall_height_px;

	wall_height_px = (int)(g->win_height / wall_dist);
	ray->top_px = g->win_height / 2 - wall_height_px / 2;
	if (ray->top_px < 0)
		ray->top_px = 0;
	ray->bottom_px = g->win_height / 2 + wall_height_px / 2;
	if (ray->bottom_px >= g->win_height)
		ray->bottom_px = g->win_height - 1;
}

static int	get_side_color(t_side side)
{
	if (side == NO)
		return (WALL_COLOR_NO);
	if (side == SO)
		return (WALL_COLOR_SO);
	if (side == EA)
		return (WALL_COLOR_EA);
	if (side == DOOR_CLOSED)
		return (DOOR_COLOR_CLOSED);
	return (WALL_COLOR_WE);
}

static void	draw_vertical_screen_line(t_ray *ray, int x, t_game *g)
{
	int		y;

	set_wall_screen_boundaries(ray, ray->wall_dist, g);
	y = 0;
	while (y < ray->top_px)
		mlx_put_pixel(g->screen, x, y++, g->map->color_c.rgb);
	if (COLOR_MODE)
	{
		y = ray->top_px;
		while (y < ray->bottom_px)
			mlx_put_pixel(g->screen, x, y++, get_side_color(ray->side));
	}
	else
		render_textured_wall(ray, x, g);
	y = ray->bottom_px;
	while (y < g->win_height)
		mlx_put_pixel(g->screen, x, y++, g->map->color_f.rgb);
}

void	draw_view_on_screen(t_game *g)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < g->win_width)
	{
		cast_one_ray(&ray, x, g);
		draw_vertical_screen_line(&ray, x, g);
		x++;
	}
}
