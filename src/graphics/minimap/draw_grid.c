#include "cub3d.h"

static void	draw_minimap_cell(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < MN_SCALE - 1)
	{
		j = 0;
		while (j < MN_SCALE - 1)
		{
			mlx_put_pixel(game->minimap,
				x * MN_SCALE + i, y * MN_SCALE + j, color);
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
			if (game->map->grid[y][x] == '1')
				draw_minimap_cell(game, x, y, 0xFFFFFFFF);
			else
				draw_minimap_cell(game, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}
