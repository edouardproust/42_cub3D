#include "cub3d.h"

static void	draw_minimap_cell(t_game *game, int x, int y, bool is_wall)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < MN_SCALE)
	{
		j = 0;
		while (j < MN_SCALE)
		{
			color = MN_COLOR_WALL;
			if (i == 0 || j == 0)
				color = MN_COLOR_GRID;
			else if (!is_wall)
				color = MN_COLOR_FLOOR;
			mlx_put_pixel(game->minimap, x * MN_SCALE + i, y * MN_SCALE + j, color);
			j++;
		}
		i++;
	}
}
static void	draw_minimap_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->grid_rows)
	{
		x = 0;
		while (x < game->map->grid_cols)
		{
			draw_minimap_cell(game, x, y, game->map->grid[y][x] == '1');
			x++;
		}
		y++;
	}
}

static void	init_player(t_game *g)
{
	t_point			pos_px;
	mlx_texture_t	*tx;

	pos_px.x = g->pos.x * MN_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->pos.y * MN_SCALE + g->minimap->instances[0].y;
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
 * @param g Pointer to the game structure.
 *
 * Key Notes:
 * - ft_memset sets all minimap pixels to transparent (0x00000000) on creation.
 *   (MLX images have uninitialized pixel data by default.)
 * - sizeof(int32_t): Each pixel is a 4-byte RGBA value.
 */
void	init_minimap(t_game *g)
{
	int	mm_width;
	int	mm_height;

	mm_width = g->map->grid_cols * MN_SCALE;
	mm_height = g->map->grid_rows * MN_SCALE;
	g->minimap = mlx_new_image(g->mlx, mm_width, mm_height);
	if (!g->minimap)
		exit_game("Minimap creation failed", g);
	clear_image_pixels(g->minimap);
	mlx_image_to_window(g->mlx, g->minimap, MN_X, g->win_height - mm_height - MN_Y);
	draw_minimap_grid(g);
	init_player(g);
}
