#include "cub3d.h"

void	load_textures(t_game *g)
{
	g->tex_no = mlx_load_png(g->map->texture_no);
	g->tex_so = mlx_load_png(g->map->texture_so);
	g->tex_ea = mlx_load_png(g->map->texture_ea);
	g->tex_we = mlx_load_png(g->map->texture_we);
	if (!g->tex_no || !g->tex_so || !g->tex_ea || !g->tex_we)
		exit_game("Failed to load textures", g);
}

mlx_texture_t *get_wall_texture(t_side side, t_game *g)
{
	if (side == NO)
		return (g->tex_no);
	if (side == SO)
		return (g->tex_so);
	if (side == EA)
		return (g->tex_ea);
	return (g->tex_we);
}

double	calc_wall_hit_position(t_ray *ray, t_game *g)
{
	double	wall_x;

	if (ray->side <= 1)
		wall_x = g->pos.x + ray->wall_dist * ray->dir.x;
	else
		 wall_x = g->pos.y + ray->wall_dist * ray->dir.y;
	return (wall_x - floor(wall_x));
}

int	get_texture_horizontal(mlx_texture_t *tex, t_ray *ray, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == NO || ray->side == SO) && ray->dir.x > 0)
		tex_x = tex->width - tex_x - 1;
	if ((ray->side == EA || ray->side == WE) && ray->dir.y < 0)
		tex_x = tex->width - tex_x - 1;
	 return (tex_x);
}
