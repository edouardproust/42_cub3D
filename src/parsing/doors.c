#include "cub3d.h"

static void	populate_doors(t_map *map)
{
	int x;
	int	y;
	int	index;

	y = 0;
	index = 0;
	while (y < map->grid_rows)
	{
		x = 0;
		while (x < map->grid_cols)
		{
			if (map->grid[y][x] == 'D')
			{
				map->doors[index].x = x;
				map->doors[index].y = y;
				map->doors[index].state = CLOSED;
				index++;
			}
			x++;
		}
		y++;
	}
}

void	init_doors(t_game *g)
{
	t_map	*map;
	int		count;
	int		x;
	int		y;

	map = g->map;
	y = 0;
	count = 0;
	while (y < map->grid_rows)
	{
		x = 0;
		while (x < map->grid_cols)
		{
			if (map->grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	map->door_count = count;
	if (count == 0)
	{
		map->doors = NULL;
		return ;
	}
	map->doors = ft_calloc(count, sizeof(t_door));
	if (!map->doors)
		exit_game("Door allocation failed", g);
	 populate_doors(map);
}
