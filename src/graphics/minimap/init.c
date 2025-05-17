#include "cub3d.h"

static void	init_player(t_game *g)
{
	t_point			pos_px;
	mlx_texture_t	*tx;

	pos_px.x = g->player_x * MN_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->player_y * MN_SCALE + g->minimap->instances[0].y;
	tx = mlx_load_png(MM_TX_PLAYER);
	if (!tx)
		exit_game("MLX42: Invalid texture", g);
	g->mm_player = mlx_texture_to_image(g->mlx, tx);
	if (!g->mm_player)
		exit_game("Minimap player creation failed", g);
	mlx_resize_image(g->mm_player, g->mm_player->width / 3, g->mm_player->height / 3);
	mlx_image_to_window(g->mlx, g->mm_player, pos_px.x, pos_px.y);
}

/**
 * Initializes the minimap image and its pixel buffer.
 *
 * @param game Pointer to the game structure.
 *
 * Key Notes:
 * - ft_memset sets all minimap pixels to transparent (0x00000000) on creation.
 *   (MLX images have uninitialized pixel data by default.)
 * - sizeof(int32_t): Each pixel is a 4-byte RGBA value.
 */
void	init_minimap(t_game *game)
{
	int	mm_width;
	int	mm_height;
	int	minimap_height;

	mm_width = game->map->grid_cols * MN_SCALE;
	mm_height = game->map->grid_rows * MN_SCALE;
	game->minimap = mlx_new_image(game->mlx, mm_width, mm_height);
	if (!game->minimap)
		exit_game("Minimap creation failed", game);
	ft_memset(game->minimap->pixels, 0, mm_width * mm_height * sizeof(int32_t));
	minimap_height = game->map->grid_rows * MN_SCALE;
	mlx_image_to_window(game->mlx, game->minimap, MN_X,
		HEIGHT - minimap_height - MN_Y);
	init_player(game);
}
