/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g->screen = mlx_new_image(g->mlx, g->win_width, g->win_height);
	if (!g->screen)
		exit_game("Screen buffer creation failed", g);
	mlx_image_to_window(g->mlx, g->screen, 0, 0);
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
void	display_game(t_game *game)
{
	init_mlx_context(game);
	init_main_screen(game);
	load_textures(game);
	display_minimap(game);
	game->last_frame = mlx_get_time();
}
