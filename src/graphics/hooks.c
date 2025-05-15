#include "cub3d.h"

void	loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	render_minimap(game);
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

void	resize_hook(int32_t width, int32_t height, void* param)
{
	t_game			*game;
	int				minimap_height;
	mlx_instance_t	*mm_instances;

	game = (t_game *)param;
	game->win_width = width;
	game->win_height = height;
	mm_instances = game->minimap->instances;
	minimap_height = game->map->grid_rows * MN_SCALE;
	mm_instances[0].y = game->win_height - minimap_height - MN_Y;
}
