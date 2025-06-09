#include "cub3d.h"

static void	flood_fill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->grid_rows || x < 0 || x >= map->grid_cols)
		return ;
	if (map->grid[y][x] == '1' || map->grid[y][x] == ' '
		|| map->grid[y][x] == 'V' || map->grid[y][x] == 'X')
		return ;
	if (map->grid[y][x] == 'D')
	{
		map->reachable++;
		map->grid[y][x] = 'X';
	}
	if (!is_grid_player_char(map->grid[y][x]) && (map->grid[y][x]) != 'X')
	{
		map->reachable++;
		map->grid[y][x] = 'V';
	}
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}

static void	reset_flood(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->grid_rows)
	{
		x = 0;
		while (x < map->grid_cols)
		{
			if (map->grid[y][x] == 'V')
				map->grid[y][x] = '0';
			if (map->grid[y][x] == 'X')
				map->grid[y][x] = 'D';
			x++;
		}
		y++;
	}
}

void	check_map_accessibility(t_game *g)
{
	t_map	*map;
	int		y;
	int		x;

	map = g->map;
	map->reachable = 0;
	map->total_accessible = 0;
	y = 0;
	while (y < map->grid_rows)
	{
		x = 0;
		while (x < map->grid_cols)
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'X'
				|| is_grid_player_char(map->grid[y][x]))
				map->total_accessible++;
			x++;
		}
		y++;
	}
	flood_fill(map, map->start_pos.y, map->start_pos.x);
	if (map->reachable != map->total_accessible)
		exit_game2(E_PARSING, "Map is not fully accessible", g);
	reset_flood(map);
}
