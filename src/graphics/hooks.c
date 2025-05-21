#include "cub3d.h"

void	loop_hook(void *param)
{
	t_game	*game;
	double	current_time;
	double	delta;
	bool	has_moved;

	game = (void *)param;
	current_time = mlx_get_time();
	delta = current_time - game->last_frame;
	game->last_frame = current_time;
	has_moved = false;
	has_moved = move_player(game, delta);
	has_moved += rotate_player(game, delta);
	if (has_moved)
		draw_view_on_screen(game);
}

void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(EXIT_SUCCESS);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	t_keys	mapped_key;

	game = (t_game *)param;
	handle_special_keys(keydata, game);
	mapped_key = mlx_key_to_enum(keydata.key);
	if (mapped_key != KEY_COUNT)
		game->key_states[mapped_key] = (keydata.action != MLX_RELEASE);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;
	int		minimap_height;

	game = (t_game *)param;
	game->win_width = width;
	game->win_height = height;
	mlx_resize_image(game->screen, width, height);
	minimap_height = game->map->grid_rows * MM_SCALE;
	game->minimap->instances[0].y = game->win_height - minimap_height - MM_Y;
	update_minimap_player_sprite(game);
	update_minimap_dir_sprite(game);
	draw_view_on_screen(game);
}
