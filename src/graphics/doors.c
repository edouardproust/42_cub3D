#include "cub3d.h"

static int	get_door_color(t_game *g, int x, int y)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < g->map->door_count)
	{
		door = &g->map->doors[i];
		if (door->x == x && door->y == y)
		{
			if (door->state == OPEN)
				return (MM_COLOR_OPEN);
			else
				return (MM_COLOR_CLOSED);
		}
		i++;
	}
	return (MM_COLOR_CLOSED);
}

static void	draw_minimap_door_cell(t_game *g, int map_x, int map_y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	color = get_door_color(g, map_x, map_y);
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			mlx_put_pixel(g->minimap,
				map_x * MM_SCALE + i, map_y * MM_SCALE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_doors(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map->grid_rows)
	{
		x = 0;
		while (x < g->map->grid_cols)
		{
			if (g->map->grid[y][x] == 'D')
				draw_minimap_door_cell(g, x, y);
			x++;
		}
		y++;
	}
}

static bool	try_toggle_door(t_game *g, t_door *door, int px, int py)
{
	if (abs(door->x - px) > 1 || abs(door->y - py) > 1)
		return (false);
	if (door->state == OPEN && door->x == px && door->y == py)
		return (false);
	door->state = !door->state;
	draw_minimap_door_cell(g, door->x, door->y);
	g->show_door_half = true;
	g->door_half_pos = (t_point){door->x, door->y};
	return (true);
}

void	toggle_doors(t_game *g)
{
	static double	last_toggle = 0;
	int				i;
	int				p_x;
	int				p_y;
	double			current_time;

	i = 0;
	current_time = mlx_get_time();
	p_x = (int)g->pos.x;
	p_y = (int)g->pos.y;
	if (current_time - last_toggle < 0.3)
		return ;
	while (i < g->map->door_count)
	{
		if (try_toggle_door(g, &g->map->doors[i], p_x, p_y))
		{
			last_toggle = current_time;
			return ;
		}
	}
	i++;
}
