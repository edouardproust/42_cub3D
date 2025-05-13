#include "cub3d.h"

void	init_mlx(t_game *game)
{
	int	mm_width;
	int	mm_height;

	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		exit_game("MLX init failed", game);
	game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen)
		exit_game("Screen buffer creation failed", game);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	ft_memset(game->screen->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	game->minimap_scale = MN_SCALE;
	mm_width = game->map->grid_cols * MN_SCALE;
	mm_height = game->map->grid_rows * MN_SCALE;
	game->minimap = mlx_new_image(game->mlx, mm_width, mm_height);
	ft_memset(game->minimap->pixels, 0, mm_width*mm_height*sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->minimap, MN_X, MN_Y);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, render_minimap, game);
	mlx_close_hook(game->mlx, close_hook, game);
}
