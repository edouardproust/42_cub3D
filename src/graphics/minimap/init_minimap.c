#include "cub3d.h"

static void	draw_minimap_cell(t_game *game, int x, int y, bool is_wall)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			color = MM_COLOR_WALL;
			if (i == 0 || j == 0)
				color = MM_COLOR_GRID;
			else if (!is_wall)
				color = MM_COLOR_FLOOR;
			mlx_put_pixel(game->minimap, x * MM_SCALE + i, y * MM_SCALE + j, color);
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

	pos_px.x = g->pos.x * MM_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->pos.y * MM_SCALE + g->minimap->instances[0].y;
	tx = mlx_load_png(MM_PLAYER_IMG);
	if (!tx)
		exit_game("MLX42: Invalid texture", g);
	g->mm_player = mlx_texture_to_image(g->mlx, tx);
	if (!g->mm_player)
		exit_game("Minimap player creation failed", g);
	mlx_resize_image(g->mm_player, MM_PLAYR_WIDTH, g->mm_player->height * MM_PLAYR_WIDTH / g->mm_player->width);
	mlx_image_to_window(g->mlx, g->mm_player, pos_px.x - g->mm_player->width/2, pos_px.y - g->mm_player->height/2);
}

static void	init_view_direction(t_game *g)
{
	t_point			pos_px;
	mlx_texture_t	*tx;

	pos_px.x = (g->pos.x + g->dir.x) * MM_SCALE + g->minimap->instances[0].x;
	pos_px.y = (g->pos.y + g->dir.y) * MM_SCALE + g->minimap->instances[0].y;
	tx = mlx_load_png(MM_DIR_IMG);
	if (!tx)
		exit_game("MLX42: Invalid texture", g);
	g->mm_dir = mlx_texture_to_image(g->mlx, tx);
	if (!g->mm_dir)
		exit_game("Minimap viewpoint creation failed", g);
	mlx_resize_image(g->mm_dir, MM_DIR_WIDTH, g->mm_dir->height * MM_DIR_WIDTH / g->mm_dir->width);
	mlx_image_to_window(g->mlx, g->mm_dir, pos_px.x - g->mm_dir->width/2, pos_px.y - g->mm_dir->height/2);
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

	mm_width = g->map->grid_cols * MM_SCALE;
	mm_height = g->map->grid_rows * MM_SCALE;
	g->minimap = mlx_new_image(g->mlx, mm_width, mm_height);
	if (!g->minimap)
		exit_game("Minimap creation failed", g);
	clear_image_pixels(g->minimap);
	mlx_image_to_window(g->mlx, g->minimap, MM_X, g->win_height - mm_height - MM_Y);
	draw_minimap_grid(g);
	init_player(g);
	init_view_direction(g);
}
