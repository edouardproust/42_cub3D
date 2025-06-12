#include "cub3d.h"

static bool	try_toggle_door(t_door *door, int px, int py)
{
	if (abs(door->x - px) > 1 || abs(door->y - py) > 1)
		return (false);
	if (door->state == OPEN && door->x == px && door->y == py)
		return (false);
	door->state = !door->state;
	return (true);
}

void	toggle_doors(t_game *g)
{
	static double	last_toggle = 0;
	double			current_time;
	int				player_x;
	int				player_y;
	int				i;

	current_time = mlx_get_time();
	player_x = (int)g->pos.x;
	player_y = (int)g->pos.y;
	if (current_time - last_toggle < 0.3)
		return ;
	i = 0;
	while (i < g->map->door_count)
	{
		if (try_toggle_door(&g->map->doors[i], player_x, player_y))
		{
			draw_minimap_door_cell(g, g->map->doors[i].x, g->map->doors[i].y);
			last_toggle = current_time;
			g->force_redraw = true;
			return ;
		}
		i++;
	}
}
