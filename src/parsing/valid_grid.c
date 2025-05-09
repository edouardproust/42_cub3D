/**
 * @TODO
 * Grid:
 * 🟢 Must contains only the following characters: 0, 1, N, S, E, W
 * 🟢 Must be closed/surrounded by walls (char '1')
 * 🟢 Cannot contain empty lines
 * 🟢 Cannot contain spaces between walls
 * 🟢 Needs to be the last element in the file (no extra data after)
 * Allowed for grid:
 * 🟢 Spaces outside of the walls (char '1')
 *
 * If error:
 * 🟠 Clean program exit + print "Error\n" followed by detail
 * of the error
*/

#include "cub3d.h"

static void	check_grid_line(char *line, bool *player_found,
	bool *is_empty_line, t_game *g)
{
	while (*line)
	{
		if (!is_grid_char(*line))
			exit_game2(E_PARSING, "grid can contains only chars: 1, 0, N, S, E, W", g);
		if (*is_empty_line && !ft_isspace(*line))
			*is_empty_line = false;
		if (is_grid_player_char(*line))
		{
			if (*player_found)
				exit_game2(E_PARSING, "grid contains several player locations", g);
			*player_found = true;
		}
		line++;
	}
}

/**
 * @note This functions accepts empty lines after the grid, if they only
 *  contain spaces. //TODO verify with Ava that this is conform to subject
 */
void	check_grid(t_map *map, t_game *g)
{
	int		i;
	bool	player_found;
	bool	empty_line_found;
	bool	is_empty_line;

	player_found = false;
	empty_line_found = false;
	i = 0;
	while (i < map->grid_rows)
	{
		is_empty_line = true;
		check_grid_line(map->grid[i], &player_found, &is_empty_line, g);
		if (!empty_line_found && is_empty_line)
			empty_line_found = true;
		if (empty_line_found && !is_empty_line)
			exit_game2(E_PARSING, "grid contains an empty line", g);
		i++;
	}
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

bool	is_grid_closed(t_map *map)
{
	int	c;
	int	y;
	int	x;

	y = 0;
	while (y < map->grid_rows)
	{
		x = 0;
		while (x < map->grid_cols)
		{
			c = map->grid[y][x];
			set_map_player(map, x, y, c);
			if (c == '0' || is_grid_player_char(c))
			{
				if (!check_surrounding_chars(map, y, x))
					return (put_error2(E_PARSING, "Grid is not closed"), false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
