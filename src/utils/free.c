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
	free(map->color_c);
	free(map->color_f);
	free_grid(map->grid, map->grid_rows);
	free(map);
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	free_map(g->map);
	free(g);
}
