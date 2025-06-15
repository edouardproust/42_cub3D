/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Check the file extension.
 *
 * @param path The path of the file to check
 * @param ext The extension to check (must include the dot. eg ".jpg")
 * @return `true` if `path` ends by `ext`, `false` otherwise.
 */
bool	has_valid_extension(char *path, char *ext)
{
	int		ext_len;
	char	*dot_ptr;
	int		i;

	dot_ptr = ft_strrchr(path, '.');
	if (!dot_ptr)
		return (false);
	else
	{
		ext_len = ft_strlen(ext);
		i = 0;
		while (i <= ext_len)
		{
			if (*(dot_ptr + i) != ext[i])
				return (false);
			i++;
		}
	}
	return (true);
}

/**
 * Checks if there is non-whitespace content after the first space
 * @param str Input string to check (may contain \n at end)
 * @return true if non-whitespace content exists after first space group,
 *         false otherwise (including NULL or single-word strings)
 */
bool	has_more_than_one_word(char *str)
{
	if (!str)
		return (false);
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (true);
	return (false);
}

void	set_map_player(t_map *map, int x, int y, char dir)
{
	if (is_grid_player_char(dir))
	{
		map->start_pos.y = y;
		map->start_pos.x = x;
		map->start_dir = dir;
	}
}

/**
 * Validates door placement rules:
 * - Must be surrounded by walls on opposite sides
 * - Cannot be on map edges
 * - Must have non-wall adjacent cells on all four direactions
 * 
 * @param map Map data
 * @param y Door grid Y
 * @param x Door grid X
 * @return true if valid placement, false otherwise
 */
bool	is_valid_door_position(t_map *map, int y, int x)
{
	char	**grid;
	bool	horizontal;
	bool	vertical;

	grid = map->grid;
	if (y == 0 || y == map->grid_rows - 1 || x == 0 || x == map->grid_cols - 1)
		return (false);
	horizontal = (grid[y][x - 1] == '1' && grid[y][x + 1] == '1');
	vertical = (grid[y - 1][x] == '1' && grid[y + 1][x] == '1');
	if (horizontal)
	{
		if (grid[y - 1][x] != '1' || grid[y + 1][x] != '1')
			return (true);
	}
	if (vertical)
	{
		if (grid[y][x - 1] != '1' || grid[y][x + 1] != '1')
			return (true);
	}
	return (false);
}
