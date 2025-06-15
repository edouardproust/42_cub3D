#include "cub3d.h"

static void	check_grid_line(char *line, bool *player_found,
	bool *is_blank_line, t_game *g)
{
	*is_blank_line = true;
	while (*line)
	{
		if (!is_grid_char(*line))
			exit_game2(E_PARSING,
				"grid can only contain 1, 0, D, N, S, E, W and spaces", g);
		if (*is_blank_line && !ft_isspace(*line))
			*is_blank_line = false;
		if (is_grid_player_char(*line))
		{
			if (*player_found)
				exit_game2(E_PARSING,
					"grid contains several player locations", g);
			*player_found = true;
		}
		line++;
	}
}

/**
 * @note This functions accepts empty lines after the grid, if they only
 *  contain spaces.
 */
void	check_grid_lines(t_game *g)
{
	int		i;
	bool	player_found;
	bool	empty_line_found;
	bool	is_blank_line;
	bool	is_blank_grid;

	player_found = false;
	empty_line_found = false;
	is_blank_grid = true;
	i = 0;
	while (i < g->map->grid_rows)
	{
		check_grid_line(g->map->grid[i], &player_found, &is_blank_line, g);
		if (!is_blank_line)
			is_blank_grid = false;
		if (!empty_line_found && is_blank_line)
			empty_line_found = true;
		if (empty_line_found && !is_blank_line)
			exit_game2(E_PARSING, "grid contains an empty line", g);
		i++;
	}
	if (is_blank_grid)
		exit_game2(E_PARSING, "grid is empty", g);
	if (!player_found)
		exit_game2(E_PARSING, "no player location in grid", g);
}

static bool	check_surrounding_chars(t_map *map, int y, int x)
{
	int	dy;
	int	dx;
	int	ny;
	int	nx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			ny = y + dy;
			nx = x + dx;
			if (!(dx == 0 && dy == 0)
				&& (ny < 0 || ny >= map->grid_rows || nx < 0
					|| nx >= map->grid_cols || map->grid[ny][nx] == ' '))
				return (false);
			dx++;
		}
		dy++;
	}
	return (true);
}

static void	check_doors(t_game *g, int y, int x)
{
	if (!is_valid_door_position(g->map, y, x))
		exit_game2(E_PARSING, "Invalid door position", g);
}

void	check_grid_is_closed(t_game *g)
{
	int	c;
	int	y;
	int	x;

	y = 0;
	while (y < g->map->grid_rows)
	{
		x = 0;
		while (x < g->map->grid_cols)
		{
			c = g->map->grid[y][x];
			set_map_player(g->map, x, y, c);
			if (c == '0' || is_grid_player_char(c))
			{
				if (!check_surrounding_chars(g->map, y, x))
					exit_game2(E_PARSING, "Grid is not closed", g);
			}
			else if (c == 'D')
				check_doors(g, y, x);
			x++;
		}
		y++;
	}
}
