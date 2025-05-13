#include "cub3d.h"

/**
 * Initializes MLX context and main window
 * @param game Pointer to game structure
 * @return true if successful, false otherwise
 */
static bool	init_mlx_context(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		exit_game("MLX init failed", game);
		return (false);
	}
	return (true);
}

/**
 * Creates and initializes main screen buffer
 * @param game Pointer to game structure
 */
static void	init_main_screen(t_game *game)
{
	game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen)
		exit_game("Screen buffer creation failed", game);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	ft_memset(game->screen->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
}

/**
 * Initializes minimap image and positioning
 * @param game Pointer to game structure
 */
static void	init_minimap(t_game *game)
{
	int	mm_width;
	int	mm_height;
	
	game->minimap_scale = MN_SCALE;
	mm_width = game->map->grid_cols * MN_SCALE;
	mm_height = game->map->grid_rows * MN_SCALE;
	game->minimap = mlx_new_image(game->mlx, mm_width, mm_height);
	if (!game->minimap)
		exit_game("Minimap creation failed", game);
	ft_memset(game->minimap->pixels, 0, mm_width * mm_height * sizeof(int32_t));
	mlx_image_to_window(game->mlx, game->minimap, MN_X, MN_Y);
}

/**
 * Registers all MLX hooks and callbacks
 * @param game Pointer to game structure
 */
static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, render_minimap, game);
	mlx_close_hook(game->mlx, close_hook, game);
}

/**
 * High-level initialization of MLX components
 * @param game Pointer to game structure
 * 
 * Manages the initialization sequence:
 * 1. MLX context creation
 * 2. Main screen setup
 * 3. Minimap initialization
 * 4. Hook registration
 * 5. Time tracking initialization
 */
void	init_mlx(t_game *game)
{
	if (!init_mlx_context(game))
		return;
	init_main_screen(game);
	init_minimap(game);
	setup_hooks(game);
	game->last_frame = mlx_get_time();
}
