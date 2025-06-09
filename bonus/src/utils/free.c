#include "cub3d.h"

void	free_grid(char **grid, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(grid[i++]);
	free(grid);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free(map->texture_no);
	free(map->texture_so);
	free(map->texture_ea);
	free(map->texture_we);
	free(map->color_c.str);
	free(map->color_f.str);
	free_grid(map->grid, map->grid_rows);
	free(map);
}

static void	free_textures(t_game *g)
{
	if (g->tex_no)
		mlx_delete_texture(g->tex_no);
	if (g->tex_so)
		mlx_delete_texture(g->tex_so);
	if (g->tex_ea)
		mlx_delete_texture(g->tex_ea);
	if (g->tex_we)
		mlx_delete_texture(g->tex_we);
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx)
	{
		if (g->screen)
			mlx_delete_image(g->mlx, g->screen);
		if (g->minimap)
			mlx_delete_image(g->mlx, g->minimap);
		if (g->mm_dir)
			mlx_delete_image(g->mlx, g->mm_dir);
		if (g->mm_player)
			mlx_delete_image(g->mlx, g->mm_player);
		free_textures(g);
		mlx_terminate(g->mlx);
	}
	free_map(g->map);
	free(g);
}
