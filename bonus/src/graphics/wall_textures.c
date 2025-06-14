#include "cub3d.h"
/**
 * Loads all textures from paths specified in the map file into MLX textures.
 * Exits game on failure to load any texture.
 *
 * @param g Game structure containing map texture paths
 */
void	load_textures(t_game *g)
{
	g->tex_no = mlx_load_png(g->map->texture_no);
	g->tex_so = mlx_load_png(g->map->texture_so);
	g->tex_ea = mlx_load_png(g->map->texture_ea);
	g->tex_we = mlx_load_png(g->map->texture_we);
	g->tex_door = mlx_load_png(g->map->texture_door);
	if (!g->tex_no || !g->tex_so || !g->tex_ea || !g->tex_we
		|| !g->tex_door)
		exit_game("Failed to load wall textures", g);
}

/**
 * Selects appropriate wall texture based on which side was hit.
 *
 * @param side Wall side (NO/SO/EA/WE)
 * @param g Game structure with loaded textures
 * @return mlx_texture_t* Pointer to selected texture
 */
mlx_texture_t	*get_wall_texture(t_side side, t_game *g)
{
	if (side == NO)
		return (g->tex_no);
	if (side == SO)
		return (g->tex_so);
	if (side == EA)
		return (g->tex_ea);
	if (side == WE)
		return (g->tex_we);
	return (g->tex_door);
}

/**
 * Calculates horizontal hit position on wall surface (0.0-1.0).
 * Uses floor() to isolate fractional part of wall coordinate.
 * 
 * @param ray Ray data containing hit distance and direction
 * @param g Game structure with player position
 * @return double Position along wall width (0.0 = left edge, 1.0 = right edge)
 */
double	calc_wall_hit_position(t_ray *ray, t_game *g)
{
	double	wall_x;

	if (ray->side == NO || ray->side == SO)
	{
		wall_x = g->pos.x + ray->wall_dist * ray->dir.x;
		if (ray->side == DOOR_CLOSED && ray->is_vertical_hit)
			wall_x = g->pos.y + ray->wall_dist * ray->dir.y;
	}	
	else
	{
		wall_x = g->pos.y + ray->wall_dist * ray->dir.y;
		if (ray->side == DOOR_CLOSED && !ray->is_vertical_hit)
			wall_x = g->pos.x + ray->wall_dist * ray->dir.x;
	}
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

/**
 * Converts wall hit position to texture column index.
 * 
 * @param tex Texture to get from
 * @param ray Ray data containing hit side and direction
 * @param wall_x Fractional wall position from calc_wall_hit_position()
 * @return int X-coordinate in texture pixels (0 to width-1)
 */
int	get_texture_horizontal(mlx_texture_t *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
