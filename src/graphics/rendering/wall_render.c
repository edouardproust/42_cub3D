#include "cub3d.h"

static void	calc_vertical_scale(t_ray *ray, mlx_texture_t *tex,
		double *step, double *tex_pos)
{
	*step = 1.0 * tex->height / (ray->bottom_px - ray->top_px);
	*tex_pos = (ray->top_px - HEIGHT / 2 +
		(ray->bottom_px - ray->top_px) / 2) * (*step);
}

static void	draw_textured_pixels(int x, t_ray *ray, t_game *g, 
		mlx_texture_t *tex, int tex_x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	uint8_t	*pixel;

	calc_vertical_scale(ray, tex, &step, &tex_pos);
	y = ray->top_px;
	while (y++ < ray->bottom_px)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
		mlx_put_pixel(g->screen, x, y, 
			pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | 0xFF);
		tex_pos += step;
	}
}

void	render_textured_wall(t_ray *ray, int x, t_game *g)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;

	tex = get_wall_texture(ray->side, g);
	wall_x = calc_wall_hit_position(ray, g);
	tex_x = get_texture_horizontal(tex, ray, wall_x);
	draw_textured_pixels(x, ray, g, tex, tex_x);
}
