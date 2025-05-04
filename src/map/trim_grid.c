#include "cub3d.h"

int	trim_empty_lines_after_grid(t_map *map)
{
	int		new_h;
	int		i;
	char	**new_grid;

	new_h = map->grid_height;
	while (new_h > 0 && is_blank_str(map->grid[new_h - 1]))
		new_h--;
	if (new_h != map->grid_height)
	{
		i = new_h;
		while (i < map->grid_height)
			free((map->grid)[i++]);
		new_grid = ft_realloc(map->grid, map->grid_height * sizeof(char *),
				new_h * sizeof(char *));
		if (!new_grid)
			return (put_error2(E_PARSING, "grid realloc"), EXIT_FAILURE);
		map->grid = new_grid;
		map->grid_height = new_h;
	}
	return (EXIT_SUCCESS);
}

static void	set_grid_target_boundaries(t_map *map, int *left_bound,
	int *right_bound)
{
	int	first_non_space;
	int	last_non_space;
	int	line_len;
	int	i;

	*left_bound = INT_MAX;
	*right_bound = 0;
	i = 0;
	while (i < map->grid_height)
	{
		line_len = ft_strlen(map->grid[i]);
		first_non_space = count_space_chars(map->grid[i], 0, line_len, false);
		last_non_space = line_len - count_space_chars(map->grid[i], 0,
				line_len, true) - 1;
		if (first_non_space < *left_bound)
			*left_bound = first_non_space;
		if (last_non_space > *right_bound)
			*right_bound = last_non_space;
		i++;
	}
}

static char	*build_new_line(t_map *map, char *line, int left_bound)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char *) * (map->grid_width + 1));
	if (!new_line)
		return (put_error2(E_FATAL_PARSING, "uniformize grid"), NULL);
	i = 0;
	while (i < map->grid_width && line[left_bound + i])
	{
		new_line[i] = line[left_bound + i];
		i++;
	}
	while (i < map->grid_width)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	return (new_line);
}

int	uniformize_grid_margins(t_map *map)
{
	int		left_bound;
	int		right_bound;
	int		i;
	char	*new_line;

	set_grid_target_boundaries(map, &left_bound,
		&right_bound);
	map->grid_width = right_bound - left_bound + 1;
	i = 0;
	while (i < map->grid_height)
	{
		new_line = build_new_line(map, map->grid[i], left_bound);
		if (!new_line)
			return (EXIT_FAILURE);
		free(map->grid[i]);
		map->grid[i] = new_line;
		i++;
	}
	return (EXIT_SUCCESS);
}
