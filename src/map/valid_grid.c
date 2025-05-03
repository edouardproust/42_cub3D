/**
 * @TODO
 * Grid:
 * 🟢 Must contains only the following characters: 0, 1, N, S, E, W
 * ⭕ Must be closed/surrounded by walls (char '1')
 * 🟢 Cannot contain empty lines
 * 🟢 Needs to be the last element in the file (no extra data after)
 * Allowed for grid:
 * 🟢 Spaces outside of the walls (char '1')
 *
 * If error:
 * 🟠 Clean program exit + print "Error\n" followed by detail
 * of the error
*/

#include "cub3d.h"

static bool	is_grid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_valid_grid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || is_grid_player_char(c));
}

#include <stdlib.h>

/**
 * - Trim empty lines after grid
 * - Set `map->grid_width`
 */
bool	is_valid_grid(t_map *map)
{
	int		i;
	int		j;
	char	*line;
	bool	player_found;
	bool	is_empty_line;

	player_found = false;
	i = 0;
	while (i < map->grid_height)
	{
		line = map->grid[i];
		is_empty_line = true;
		j = 0;
		while (line[j])
		{
			if (!is_valid_grid_char(line[j]))
				return (put_error2(E_PARSING, "grid can contains only chars: 1, 0, N, S, E, W"),
					EXIT_FAILURE);
			if (!ft_isspace(line[j]))
				is_empty_line = false;
			if (is_grid_player_char(line[j]))
			{
				if (player_found)
					return (put_error2(E_PARSING, "grid contains several player locations"),
						EXIT_FAILURE);
				player_found = true;
			}
			j++;
		}
		if (is_empty_line)
			return (put_error2(E_PARSING, "grid contains an empty line"), EXIT_FAILURE);
		// Set grid width
		if (j > map->grid_width)
			map->grid_width = j;
		i++;
	}
	if (!player_found)
		return (put_error2(E_PARSING, "no player location in grid"), EXIT_FAILURE);
	return (true);
}
