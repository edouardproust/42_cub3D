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

static void	handle_door_toggle(t_game *g, t_door *door)
{
	draw_minimap_door_cell(g, door->x, door->y);
	g->show_door_half = true;
	g->door_half_pos = (t_point){door->x, door->y};
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
			handle_door_toggle(g, &g->map->doors[i]);
			last_toggle = current_time;
			g->force_redraw = true;
			return ;
		}
		i++;
	}
}
