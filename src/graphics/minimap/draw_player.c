#include "cub3d.h"

void	draw_player_circle(t_game *game)
{
	int	px;
	int	py;
	int	dx;
	int	dy;
	int	radius;

	px = (int)(game->player_x * game->minimap_scale);
	py = (int)(game->player_y * game->minimap_scale);
	radius = PLAYER_RADIUS;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				mlx_put_pixel(game->minimap, px + dx, py + dy, 0xFF0000FF);
			dx++;
		}
		dy++;
	}
}
