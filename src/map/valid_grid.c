/**
 * @TODO
 * Grid:
 * 🟢 Must contains only the following characters: 0, 1, N, S, E, W
 * ⭕ Must be closed/surrounded by walls (char '1')
 * 🟢 Cannot contain empty lines
 * ⭕ Cannot contain spaces between walls
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

static bool	is_valid_grid_line(char *line, bool *player_found,
	bool *is_empty_line)
{
	while (*line)
	{
		if (!is_valid_grid_char(*line))
			return (put_error2(E_PARSING,
					"grid can contains only chars: 1, 0, N, S, E, W"), false);
		if (*is_empty_line && !ft_isspace(*line))
			*is_empty_line = false;
		if (is_grid_player_char(*line))
		{
			if (*player_found)
				return (put_error2(E_PARSING,
						"grid contains several player locations"), false);
			*player_found = true;
		}
		line++;
	}
	return (true);
}

/**
 * @note This functions accepts empty lines after the grid, if they only
 *  contain spaces. //TODO verify with Ava that this is conform to subject
 */
bool	is_prevalid_grid(t_map *map)
{
	int		i;
	bool	player_found;
	bool	empty_line_found;
	bool	is_empty_line;

	player_found = false;
	empty_line_found = false;
	i = 0;
	while (i < map->grid_height)
	{
		is_empty_line = true;
		if (!is_valid_grid_line(map->grid[i], &player_found, &is_empty_line))
			return (false);
		if (!empty_line_found && is_empty_line)
			empty_line_found = true;
		if (empty_line_found && !is_empty_line)
			return (put_error2(E_PARSING, "grid contains an empty line"),
				false);
		i++;
	}
	if (!player_found)
		return (put_error2(E_PARSING, "no player location in grid"), false);
	return (true);
}

bool	is_valid_grid(t_map *map)
{
	debug_parsed_map(map); //DEBUG
	//has_grid_holes(map->grid); //TODO
	//is_grid_closed_by_walls(map->grid); //TODO
	//set_player_position_and_dir(map->grid); //TODO
	return (true);
}
