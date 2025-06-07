#include "cub3d.h"

/**
 * @note redraw the 3D view on 30fps (instead of 60)
 */
static void	loop_hook(void *param)
{
	static int	frame_count = 0;
	t_game		*game;
	double		current_time;
	double		delta;
	bool		has_moved;

	game = (void *)param;
	current_time = mlx_get_time();
	delta = current_time - game->last_frame;
	game->last_frame = current_time;
	has_moved = move_player(game, delta);
	has_moved |= rotate_player(game, delta);
	has_moved |= handle_mouse_rotation(game, delta);
	frame_count++;
	if ((has_moved && frame_count % 2 == 0) || frame_count == 1)
		draw_view_on_screen(game);
	if (has_moved && game->minimap_visible)
		draw_player(game);
}

static void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(EXIT_SUCCESS);
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	t_keys	mapped_key;

	game = (t_game *)param;
	handle_special_keys(keydata, game);
	mapped_key = mlx_key_to_enum(keydata.key);
	if (mapped_key != KEY_COUNT)
		game->key_states[mapped_key] = (keydata.action != MLX_RELEASE);
}

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;
	int		minimap_height;

	game = (t_game *)param;
	game->win_width = width;
	game->win_height = height;
	if (game->mouse_captured)
		mlx_set_mouse_pos(game->mlx, width / 2, height / 2);
	mlx_resize_image(game->screen, width, height);
	if (game->minimap)
	{
		minimap_height = game->map->grid_rows * MM_SCALE;
		game->minimap->instances[0].y
			= game->win_height - minimap_height - MM_Y;
		update_minimap_player_sprite(game);
		update_minimap_dir_sprite(game);
	}
	draw_view_on_screen(game);
}

/**
 * Registers all MLX hooks and callbacks
 * @param game Pointer to game structure
 */
void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_close_hook(game->mlx, close_hook, game);
	mlx_resize_hook(game->mlx, resize_hook, game);
	if (game->mouse_captured)
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
}
