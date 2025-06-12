#include "cub3d.h"

void	trim_empty_lines_after_grid(t_game *g)
{
	int		new_h;
	int		i;
	char	**new_grid;

	new_h = g->map->grid_rows;
	while (new_h > 0 && is_blank_str(g->map->grid[new_h - 1]))
		new_h--;
	if (new_h == g->map->grid_rows)
		return ;
	i = new_h;
	while (i < g->map->grid_rows)
		free((g->map->grid)[i++]);
	g->map->grid_rows = new_h;
	new_grid = ft_realloc(g->map->grid,
			g->map->grid_rows * sizeof(char *), new_h * sizeof(char *));
	if (!new_grid)
		exit_game2(E_FATAL_PARSING, "grid realloc", g);
	g->map->grid = new_grid;
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
	while (i < map->grid_rows)
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

static char	*build_new_line(t_game *g, char *line, int left_bound)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char *) * (g->map->grid_cols + 1));
	if (!new_line)
		exit_game2(E_FATAL_PARSING, "uniformize grid", g);
	i = 0;
	while (i < g->map->grid_cols && line[left_bound + i])
	{
		new_line[i] = line[left_bound + i];
		i++;
	}
	while (i < g->map->grid_cols)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	return (new_line);
}

void	uniformize_grid_margins(t_game *g)
{
	int		left_bound;
	int		right_bound;
	int		i;
	char	*new_line;

	set_grid_target_boundaries(g->map, &left_bound,
		&right_bound);
	g->map->grid_cols = right_bound - left_bound + 1;
	i = 0;
	while (i < g->map->grid_rows)
	{
		new_line = build_new_line(g, g->map->grid[i], left_bound);
		free(g->map->grid[i]);
		g->map->grid[i] = new_line;
		i++;
	}
}
