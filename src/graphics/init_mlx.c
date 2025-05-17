#include "cub3d.h"
/**
 * Initializes MLX context and main window
 * @param game Pointer to game structure
 * @return void. Exits + frees program in case of failure
 */
static void	init_mlx_context(t_game *g)
{
	g->win_width = WIDTH;
	g->win_height = HEIGHT;
	g->mlx = mlx_init(g->win_width, g->win_height, "cub3D", true);
	if (!g->mlx)
		exit_game("MLX init failed", g);
}

/**
 * Creates and initializes main screen buffer
 * @param game Pointer to game structure
 *
 * Notes:
 * - ft_memset sets all pixels to transparent (0x00000000) on creation.
 *   (MLX images have uninitialized pixel data by default.)
 * - sizeof(int32_t): Each pixel is a 4-byte RGBA value.
 */
static void	init_main_screen(t_game *g)
{
	g->screen = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->screen)
		exit_game("Screen buffer creation failed", g);
	mlx_image_to_window(g->mlx, g->screen, 0, 0);
	clear_image_pixels(g->screen);
}

/**
 * Registers all MLX hooks and callbacks
 * @param game Pointer to game structure
 */
static void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_close_hook(game->mlx, close_hook, game);
	mlx_resize_hook(game->mlx, resize_hook, game);
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
	init_mlx_context(game);
	init_main_screen(game);
	init_minimap(game);
	setup_hooks(game);
	game->last_frame = mlx_get_time();
}
