#include "cub3d.h"
/**
 * Calculates vertical scaling parameters for perspective correction.
 * 
 * @param ray Ray data with screen Y boundaries
 * @param tex Texture being rendered
 * @param step Output: Vertical step per screen pixel (texture/screen ratio)
 * @param tex_pos Output: Initial texture Y position
 */
static void	calc_vertical_scale(t_ray *ray, mlx_texture_t *tex,
		double *step, double *tex_pos)
{
	int	line_height;

	line_height = ray->bottom_px - ray->top_px;
	*step = (double)tex->height / line_height;
	*tex_pos = (ray->top_px - HEIGHT / 2 + line_height / 2) * *step;
}

/**
 * Renders vertical texture part to screen column.
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
	calc_vertical_scale(ray, tex, &step, &tex_pos);
	y = ray->top_px;
	while (y <= ray->bottom_px)
	{
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
	tex_x = get_texture_horizontal(tex, ray, wall_x);
	draw_textured_pixels(x, ray, g, tex_x);
}
