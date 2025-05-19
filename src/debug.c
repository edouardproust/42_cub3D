//DEBUG Delete this file before evaluation
//DEBUG Remove links to this file in: Makefile and headers

#include "cub3d.h"

static void	print_char_repeat_nl(char c, int n)
{
	printf(" \t");
	while (n >= 0)
	{
		printf("%c", c);
		n--;
	}
	printf("\n");
}

static void	print_grid(t_map *map)
{
	int	i;

	if (map->grid_cols != -1)
	{
		printf("grid:\n");
		print_char_repeat_nl('-', map->grid_cols + 1);
		i = 0;
		while (i < map->grid_rows)
		{
			printf("%d\t|%s|\n", i, map->grid[i]);
			i++;
		}
		print_char_repeat_nl('-', map->grid_cols + 1);
	}
	else
		printf("grid: (null)\n");
}

void	debug_parsed_map(t_map *map)
{
	printf("\n🐞 DEBUG:\n");
	printf("texture_no: '%s'\n", map->texture_no);
	printf("texture_so: '%s'\n", map->texture_so);
	printf("texture_ea: '%s'\n", map->texture_ea);
	printf("texture_we: '%s'\n", map->texture_we);
	printf("color_c: '%s'\n", map->color_c);
	printf("color_f: '%s'\n", map->color_f);
	print_grid(map);
	printf("grid_rows: %d\n", map->grid_rows);
	printf("grid_cols: %d\n", map->grid_cols);
	printf("start_pos: [x:%d, y:%d]\n", map->start_pos.x, map->start_pos.y);
	printf("start_dir: %c\n", map->start_dir);
	printf("\n");
}
