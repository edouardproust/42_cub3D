#include "cub3d.h"

void	render_minimap(void *param)
{
	t_game	*game;
	double	current_time;
	double	delta;

	game = (t_game *)param;
	current_time = mlx_get_time();
	delta = current_time - game->last_frame;
	game->last_frame = current_time;
	update_movement(game, delta);
	ft_memset(game->minimap->pixels, 0,
		game->minimap->width * game->minimap->height * sizeof(int32_t));
	draw_minimap_grid(game);
	draw_player_circle(game);
}
