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
	free_grid(map->grid, map->grid_height);
	free(map);
}

void	free_data(t_data **d)
{
	if (!d && !*d)
		return ;
	free_map((*d)->map);
	free(*d);
	*d = NULL;
}
