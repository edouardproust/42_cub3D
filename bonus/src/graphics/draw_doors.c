/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/**
 * Determines the minimap color for a door at given grid coordinates.
 * Searches through the door list to find a door at (x,y) and returns
 * the color based on its state (open/closed).
 * 
 * @param g Game context pointer
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @return MM_COLOR_OPEN or MM_COLOR_CLOSED (default if door not found)
 */
static int	get_door_color(t_game *g, int x, int y)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < g->map->door_count)
	{
		door = &g->map->doors[i];
		if (door->x == x && door->y == y)
		{
			if (door->state == OPEN)
				return (MM_COLOR_OPEN);
			else
				return (MM_COLOR_CLOSED);
		}
		i++;
	}
	return (MM_COLOR_CLOSED);
}

/**
 * Draws a single door cell on the minimap at specified grid coordinates.
 * Fills a MM_SCALE x MM_SCALE pixel area with the door's color.
 * 
 * @param g Game context pointer
 * @param map_x Grid X coordinate
 * @param map_y Grid Y coordinate
 */
void	draw_minimap_door_cell(t_game *g, int map_x, int map_y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	color = get_door_color(g, map_x, map_y);
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			mlx_put_pixel(g->minimap,
				map_x * MM_SCALE + i, map_y * MM_SCALE + j, color);
			j++;
		}
		i++;
	}
}

/**
 * Iterates through the entire map grid and draws all 'D' (door) cells
 * onto the minimap using draw_minimap_door_cell().
 * 
 * @param g Game context pointer
 */
void	draw_minimap_doors(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map->grid_rows)
	{
		x = 0;
		while (x < g->map->grid_cols)
		{
			if (g->map->grid[y][x] == 'D')
				draw_minimap_door_cell(g, x, y);
			x++;
		}
		y++;
	}
}

/**
 * Finds and returns a door structure at specified grid coordinates.
 * 
 * @param map Map data pointer
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @return Pointer to door structure, or NULL if not found
 */
t_door	*get_door_pos(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}
