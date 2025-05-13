#include "cub3d.h"

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

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W)
		game->key_w = (keydata.action != MLX_RELEASE);
	else if (keydata.key == MLX_KEY_S)
		game->key_s = (keydata.action != MLX_RELEASE);
	else if (keydata.key == MLX_KEY_A)
		game->key_a = (keydata.action != MLX_RELEASE);
	else if (keydata.key == MLX_KEY_D)
		game->key_d = (keydata.action != MLX_RELEASE);
}
