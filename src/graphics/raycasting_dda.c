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
				if (door->state == OPEN)
					continue ;
				else
					ray->side = DOOR_CLOSED;
			}
			ray->wall_hit = true;
		}
	}
}
