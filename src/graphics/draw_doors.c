#include "cub3d.h"

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

static void	draw_minimap_door_cell(t_game *g, int map_x, int map_y)
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

void	toggle_doors(t_game *g)
{
	int		i;
	int		player_x;
	int		player_y;
	t_door	*door;

	i = 0;
	player_x = (int)g->pos.x;
	player_y = (int)g->pos.y;
	while (i < g->map->door_count)
	{
		door = &g->map->doors[i];
		if (abs(door->x - player_x) <= 1 && abs(door->y - player_y) <= 1)
		{
			door->state = !door->state;
			draw_minimap_door_cell(g, door->x, door->y);
			return ;
		}
		i++;
	}
}
