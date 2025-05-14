#include "cub3d.h"

static void calc_ray_direction(t_ray *ray, double screen_px_col, t_game *g)
{
	double	ray_screen_factor;

	ray_screen_factor = 2 * screen_px_col / SCREEN_WIDTH_PX - 1;
	ray->dir.x = g->dir.x + g->camera_plane.x * ray_screen_factor;
	ray->dir.y = g->dir.y + g->camera_plane.y * ray_screen_factor;
}

// TODO use commented lines to remove fish eye effet. Try understand why it works...
static void	calc_ray_step_lengths(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->len_step_x = INFINITY;
	else
	{
		ray->len_step_x = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
		//ray->len_step_x = fabs(1 / ray->dir.x);
	}
	if (ray->dir.y == 0)
		ray->len_step_y = INFINITY;
	else
	{
		ray->len_step_y = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
		//ray->len_step_y = fabs(1 / ray->dir.y);
	}
}

// calculate initial length of ray (to the closest vert. or horiz. grid line)
static void calc_ray_initial_length(t_ray *ray, t_game *g)
{
	if (ray->dir.x < 0)
		ray->length_x = (g->pos.x - ray->cell.x) * ray->len_step_x;
	else
		ray->length_x = (ray->cell.x + 1 - g->pos.x) * ray->len_step_x;
	if (ray->dir.y < 0)
		ray->length_y = (g->pos.y - ray->cell.y) * ray->len_step_y;
	else
		ray->length_y = (ray->cell.y + 1 - g->pos.y) * ray->len_step_y;
}

static void calc_next_cell_move(t_ray *ray)
{
	if (ray->dir.x >= 0)
		ray->cell_move.x = 1;
	else
		ray->cell_move.x = -1;
	if (ray->dir.y >= 0)
		ray->cell_move.y = 1;
	else
		ray->cell_move.y = -1;
}

static void	perform_dda_algorythm(t_ray *ray, t_game *g)
{
	ray->wall_hit = false;
	while (!ray->wall_hit)
	{
		if (ray->length_x < ray->length_y)
		{
			ray->length_x += ray->len_step_x;
			ray->cell.x += ray->cell_move.x;
			if (ray->dir.x > 0)
				ray->side = EA;
			else
				ray->side = WE;
		}
		else
		{
			ray->length_y += ray->len_step_y;
			ray->cell.y += ray->cell_move.y;
			if (ray->dir.y > 0)
				ray->side = SO;
			else
				ray->side = NO;
		}
		if (g->map->grid[ray->cell.y][ray->cell.x] == '1')
			ray->wall_hit = true;
	}
}

double	fix_fish_eye_effect(t_ray ray, double ray_len)
{
	double	ray_dir_magnitude;

	ray_dir_magnitude = sqrt(ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
    return (ray_len / ray_dir_magnitude);
}

/**
 * @param screen_px_col	Index of the column of pixel on the screen, starting form the left
 */
double	get_ray_length(double screen_px_col, t_game *g)
{
	t_ray	ray;
	double	ray_len;

	calc_ray_direction(&ray, screen_px_col, g);
	ray.cell.x = (int)g->pos.x;
	ray.cell.y = (int)g->pos.y;
	calc_ray_step_lengths(&ray);
	calc_ray_initial_length(&ray, g);
	calc_next_cell_move(&ray);
	perform_dda_algorythm(&ray, g);
	if (ray.side == EA || ray.side == WE)
		ray_len = ray.length_x - ray.len_step_x;
	else
		ray_len = ray.length_y - ray.len_step_y;
	if (!FISHEYE_EFFECT)
		return (fix_fish_eye_effect(ray, ray_len));
	return (ray_len);
}