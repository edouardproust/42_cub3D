#include "cub3d.h"
/**
 * Initializes minimap image and positioning
 * @param game Pointer to game structure
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
