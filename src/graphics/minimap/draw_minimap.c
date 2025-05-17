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

void	refresh_minimap_player(t_game *g)
{
	t_point			pos_px;

	pos_px.x = g->player_x * MN_SCALE + g->minimap->instances[0].x;
	pos_px.y = g->player_y * MN_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = pos_px.x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = pos_px.y - g->mm_player->height / 2;
}

/**
 * Renders the minimap every frame. Responsible for:
 * - Updating player movement
 * - Clearing and redrawing the minimap
 * 
 * @param param Pointer to the game structure (t_game*).
 * 
 * Key Notes:
 * - Uses ft_memset to clear the minimap's pixel buffer to transparent
 *   (0x00000000) before redrawing. This prevents old frames lingering.
 * - sizeof(int32_t): Each pixel is a 4-byte RGBA value.
 */
void	refresh_minimap(t_game *game)
{
	double	current_time;
	double	delta;

	current_time = mlx_get_time();
	delta = current_time - game->last_frame;
	game->last_frame = current_time;
	update_movement(game, delta);
	ft_memset(game->minimap->pixels, 0,
		game->minimap->width * game->minimap->height * sizeof(int32_t));
	draw_minimap_grid(game);
	refresh_minimap_player(game);
}
