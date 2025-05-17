#include "cub3d.h"

void	loop_hook(void *param)
{
	t_game	*game;

	game = (void *)param;
	refresh_minimap(game);
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
