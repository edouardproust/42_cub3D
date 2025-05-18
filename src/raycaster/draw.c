#include "cub3d.h"

/**
 * Get how many pixels to draw on the screen to project the
 * wall height for the current ray.
 */
static void	set_wall_screen_boundaries(int *top_px, int *bottom_px, double wall_dist, t_game *g)
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

static void	print_wall_line(int x, int top_px, int bottom_px, int color, t_game *g)
{
	int	y;

	y = 0;
	while (y < top_px)
		mlx_put_pixel(g->screen, x, y++, g->map->color_c.rgb);
	while (y < bottom_px)
		mlx_put_pixel(g->screen, x, y++, color);
	while (y < (int)g->screen->height)
		mlx_put_pixel(g->screen, x, y++, g->map->color_f.rgb);
}

void	cast_rays(t_game *g)
{
	t_ray	ray;
	int		x;
	int		top_px;
	int		bottom_px;

	clear_image_pixels(g->screen);//TODO keep?
	x = 0;
	while (x < g->win_width)
	{
		cast_one_ray(&ray, x, g);
		set_wall_screen_boundaries(&top_px, &bottom_px, ray.wall_dist, g);
		//printf("DEBUG: %d: ray_len: %lf, top_px: %d, bottom_px: %d)\n", x, ray.wall_dist, top_px, bottom_px);
		if (COLOR_MODE)
			print_wall_line(x, top_px, bottom_px, get_side_color(ray.side), g);
		else
			exit_game("TODO: IMPLEMENT TEXTURE RENDERING\n", g); //TODO
		x++;
	}
}
