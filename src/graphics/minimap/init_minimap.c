#include "cub3d.h"
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

	mm_width = game->map->grid_cols * MN_SCALE;
	mm_height = game->map->grid_rows * MN_SCALE;
	game->minimap = mlx_new_image(game->mlx, mm_width, mm_height);
	if (!game->minimap)
		exit_game("Minimap creation failed", game);
	ft_memset(game->minimap->pixels, 0, mm_width * mm_height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->minimap, MN_X, MN_Y);
}
