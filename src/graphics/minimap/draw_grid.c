#include "cub3d.h"

static void	draw_minimap_cell(t_game *game, int x, int y, bool is_wall)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < MN_SCALE)
	{
		j = 0;
		while (j < MN_SCALE)
		{
			color = MN_COLOR_WALL;
			if (i == 0 || j == 0)
				color = MN_COLOR_GRID;
			else if (!is_wall)
				color = MN_COLOR_FLOOR;
			mlx_put_pixel(game->minimap, x * MN_SCALE + i, y * MN_SCALE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->grid_rows)
	{
		x = 0;
		while (x < game->map->grid_cols)
		{
			draw_minimap_cell(game, x, y, game->map->grid[y][x] == '1');
			x++;
		}
		y++;
	}
}
