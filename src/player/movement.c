#include "cub3d.h"

void	update_movement(t_game *game, double move_speed)
{
    double	new_x;
    double	new_y;
	int		grid_x1;
	int		grid_x2;
	int		grid_y1;
	int		grid_y2;

	new_x = game->player_x;
	new_y = game->player_y;
    if (game->key_w)
		new_y -= move_speed;
    if (game->key_s)
		new_y += move_speed;
    if (game->key_a)
		new_x -= move_speed;
    if (game->key_d)
		new_x += move_speed;
    grid_x1 = (int)(new_x - 0.3);
    grid_x2 = (int)(new_x + 0.3);
	grid_y1 = (int)(new_y - 0.3);
	grid_y2 = (int)(new_y + 0.3);
    if (grid_y1 >= 0 && grid_y2 < game->map->grid_rows &&
        grid_x1 >= 0 && grid_x2 < game->map->grid_cols &&
		game->map->grid[grid_y1][grid_x1] != '1' &&
		game->map->grid[grid_y1][grid_x2] != '1' &&
		game->map->grid[grid_y2][grid_x1] != '1' &&
        game->map->grid[grid_y2][grid_x2] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }
}
