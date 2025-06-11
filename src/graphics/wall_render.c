#include "cub3d.h"

/**
 * Determines how much to stretch/compress the texture vertically 
 * based on wall distance
 * 
 * Key calculations:
 * - line_height = HEIGHT / distance - Closer walls appear taller
 * - step - How much to move in texture for each screen pixel
 * - tex_pos - Starting position in texture (centers the texture vertically)
 *
 * @param ray Ray data with screen Y boundaries
 * @param tex Texture being rendered
 * @param step Output: Vertical step per screen pixel (texture/screen ratio)
 * @param tex_pos Output: Initial texture Y position
 */
static double	calc_vertical_scale(t_ray *ray, mlx_texture_t *tex,
		double *step, t_game *g)
{
	int		line_height;
	double	tex_pos;

	line_height = (int)(g->win_height / ray->wall_dist);
	ray->top_px = -line_height / 2 + g->win_height / 2;
	if (ray->top_px < 0)
		ray->top_px = 0;
	ray->bottom_px = line_height / 2 + g->win_height / 2;
	if (ray->bottom_px >= g->win_height)
		ray->bottom_px = g->win_height - 1;
	*step = (double)tex->height / line_height;
	tex_pos = (ray->top_px - g->win_height / 2 + line_height / 2) * *step;
	return (tex_pos);
}

static bool	skip_bottom_half(t_ray *ray, int *y, double *tex_pos, double step)
{
	int	mid_point;

	if (ray->side != DOOR_HALF)
		return (false);
	mid_point = ray->top_px + (ray->bottom_px - ray->top_px) / 2;
	if (*y > mid_point)
	{
		(*y)++;
		*tex_pos += step;
		return (true);
	}
	return (false);
}

/**
 * Renders vertical texture part to screen column.
 * For each vertical screen pixel:
 * - Finds corresponding texture row (tex_y)
 * - Gets RGBA color from texture
 * - Paints the screen pixel
 * 
 * @param x Screen column to draw to
 * @param ray Ray data with wall dimensions
 * @param g Game structure with screen buffer
 * @param tex Texture to get from
 * @param tex_x Texture column to render
 */
static void	draw_textured_pixels(int x, t_ray *ray, t_game *g, int tex_x)
{
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;

	tex = get_wall_texture(ray->side, g);
	tex_pos = calc_vertical_scale(ray, tex, &step, g);
	y = ray->top_px;
	while (y <= ray->bottom_px)
	{
		if (skip_bottom_half(ray, &y, &tex_pos, step))
			continue ;
		tex_y = (int)tex_pos % tex->height;
		if (tex_y < 0)
			tex_y += tex->height;
		mlx_put_pixel(g->screen, x, y,
			tex->pixels[(tex_y * tex->width + tex_x) * 4 + 0] << 24
			| tex->pixels[(tex_y * tex->width + tex_x) * 4 + 1] << 16
			| tex->pixels[(tex_y * tex->width + tex_x) * 4 + 2] << 8 | 0xFF);
		tex_pos += step;
		y++;
	}
}

/**
 * Main wall rendering function. Coordinates:
 * 1. Texture selection
 * 2. Wall hit position calculation
 * 3. Texture coordinate mapping
 * 4. Pixel-by-pixel rendering
 * 
 * @param ray Raycast results for current screen column
 * @param x Screen column to render
 * @param g Game structure with textures and render target
 */
void	render_textured_wall(t_ray *ray, int x, t_game *g)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;

	tex = get_wall_texture(ray->side, g);
	wall_x = calc_wall_hit_position(ray, g);
	tex_x = get_texture_horizontal(tex, wall_x);
	draw_textured_pixels(x, ray, g, tex_x);
}
