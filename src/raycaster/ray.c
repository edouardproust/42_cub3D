#include "cub3d.h"

static void	calc_ray_step_lengths(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->len_step_x = INFINITY;
	else
	{
		if (FISHEYE_EFFECT)
			ray->len_step_x = sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
		else
			ray->len_step_x = fabs(1 / ray->dir.x);
	}
	if (ray->dir.y == 0)
		ray->len_step_y = INFINITY;
	else
	{
		if (FISHEYE_EFFECT)
			ray->len_step_y = sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
		else
			ray->len_step_y = fabs(1 / ray->dir.y);
	}
}

/**
 * Calculate initial length of ray (to the closest vert. or horiz. grid line)
 */
static void calc_initial_ray_length(t_ray *ray, t_game *g)
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

static void calc_initial_cell_move(t_ray *ray)
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

/**
 * @param screen_px_col	Index of the column of pixel on the screen, starting form the left
 */
void	cast_one_ray(t_ray *ray, double screen_px_col, t_game *g)
{
	double	ray_screen_factor;

	ray_screen_factor = 2 * screen_px_col / g->win_width - 1;
	ray->dir.x = g->dir.x + g->camera_plane.x * ray_screen_factor;
	ray->dir.y = g->dir.y + g->camera_plane.y * ray_screen_factor;
	ray->cell.x = (int)g->pos.x;
	ray->cell.y = (int)g->pos.y;
	calc_ray_step_lengths(ray);
	calc_initial_ray_length(ray, g);
	calc_initial_cell_move(ray);
	perform_dda_algorythm(ray, g);
	if (ray->side == EA || ray->side == WE)
		ray->wall_dist = ray->length_x - ray->len_step_x;
	else
		ray->wall_dist = ray->length_y - ray->len_step_y;
}
