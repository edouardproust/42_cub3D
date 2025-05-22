#include "cub3d.h"

/**
 * Get how many pixels to draw on the screen to project the
 * wall height for the current ray.
 */
static void	set_wall_screen_boundaries(int *top_px, int *bottom_px,
	double wall_dist, t_game *g)
{
	int	wall_height_px;

	wall_height_px = (int)(g->win_height / wall_dist);
	*top_px = g->win_height / 2 - wall_height_px / 2;
	if (*top_px < 0)
		*top_px = 0;
	*bottom_px = g->win_height / 2 + wall_height_px / 2;
	if (*bottom_px >= g->win_height)
		*bottom_px = g->win_height - 1;
}

static int	get_side_color(t_side side)
{
	if (side == NO)
		return (WALL_COLOR_NO);
	if (side == SO)
		return (WALL_COLOR_SO);
	if (side == EA)
		return (WALL_COLOR_EA);
	return (WALL_COLOR_WE);
}

static void	draw_vertical_screen_line(t_ray *ray, int x, t_game *g)
{
	int		y;
	int		top_px;
	int		bottom_px;

	set_wall_screen_boundaries(&top_px, &bottom_px, ray->wall_dist, g);
	if (COLOR_MODE)
	{
		y = 0;
		while (y < top_px)
			mlx_put_pixel(g->screen, x, y++, g->map->color_c.rgb);
		while (y < bottom_px)
			mlx_put_pixel(g->screen, x, y++, get_side_color(ray->side));
		while (y < (int)g->screen->height)
			mlx_put_pixel(g->screen, x, y++, g->map->color_f.rgb);
	}
	else
		exit_game("TODO: IMPLEMENT TEXTURE RENDERING\n", g); //TODO
}

void	draw_view_on_screen(t_game *g)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < g->win_width)
	{
		cast_one_ray(&ray, x, g);
		draw_vertical_screen_line(&ray, x, g);
		x++;
	}
}
