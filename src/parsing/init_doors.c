#include "cub3d.h"

static void	populate_doors(t_map *map)
{
	int	x;
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

static int	count_doors(char **grid, int rows, int cols)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_doors(t_game *g)
{
	t_map	*map;

	map = g->map;
	map->door_count = count_doors(map->grid, map->grid_rows, map->grid_cols);
	if (map->door_count == 0)
	{
		map->doors = NULL;
		return ;
	}
	map->doors = ft_calloc(map->door_count, sizeof(t_door));
	if (!map->doors)
		exit_game("Door allocation failed", g);
	populate_doors(map);
}
