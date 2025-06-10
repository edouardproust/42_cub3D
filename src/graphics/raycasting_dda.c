#include "cub3d.h"

static void	advance_ray_x(t_ray *ray)
{
	ray->length_x += ray->len_step_x;
	ray->cell.x += ray->cell_move.x;
	if (ray->dir.x > 0)
		ray->side = EA;
	else
		ray->side = WE;
}

static void	advance_ray_y(t_ray *ray)
{
	ray->length_y += ray->len_step_y;
	ray->cell.y += ray->cell_move.y;
	if (ray->dir.y > 0)
		ray->side = SO;
	else
		ray->side = NO;
}

static t_door	*get_door_pos(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

void	perform_dda_algorythm(t_ray *ray, t_game *g)
{
	t_door	*door;

	ray->wall_hit = false;
	while (!ray->wall_hit)
	{
		if (ray->length_x < ray->length_y)
			advance_ray_x(ray);
		else
			advance_ray_y(ray);
		if (g->map->grid[ray->cell.y][ray->cell.x] == '1')
			ray->wall_hit = true;
		else if (g->map->grid[ray->cell.y][ray->cell.x] == 'D')
		{
			door = get_door_pos(g->map, ray->cell.x, ray->cell.y);
			if (door)
			{
				if (g->show_door_half && door->x == g->door_half_pos.x
					&& door->y == g->door_half_pos.y)
					ray->side = DOOR_HALF;
				else if (door->state == CLOSED)
					ray->side = DOOR_CLOSED;
			}
			ray->wall_hit = true;
		}
	}
}
