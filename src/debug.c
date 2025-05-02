//DEBUG Delete this file before evaluation
//DEBUG Remove links to this file in: Makefile and headers

#include "cub3d.h"

void	debug_parsed_map(t_map *map)
{
	printf("\nDEBUG:\n");
	printf("texture_no: %s\n", map->texture_no);
	printf("texture_so: %s\n", map->texture_so);
	printf("texture_ea: %s\n", map->texture_ea);
	printf("texture_we: %s\n", map->texture_we);
	printf("color_c: %s\n", map->color_c);
	printf("color_f: %s\n", map->color_f);
	printf("grid:\n");
	int i = 0;
	while (i < map->grid_height)
		printf("[%s]\n", map->grid[i++]);
	printf("grid_height: %d\n", map->grid_height);
	printf("grid_width: %d\n", map->grid_width);
}
