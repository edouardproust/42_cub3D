#include "cub3d.h"

void	render_minimap(void *param)
{
	t_game	*game;
	double	move_speed;
	
	game = (t_game *)param;
	move_speed = 0.05;
	update_movement(game, move_speed);
	ft_memset(game->minimap->pixels, 0, 
		game->minimap->width * game->minimap->height * sizeof(int32_t));
	draw_minimap_grid(game);
	draw_player_circle(game);
}
