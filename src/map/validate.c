/**
 * @TODO
 * Metadata:
 * 🟢 Each element of data must start by the identifier, followed by
 * the correct information:
 * 		🟢 Check number of args
 * 		🟢 File exists
 * 		🟢 Identifier followed by texture path: NO, SO, WE, EA
 * 		🟢 Identifiers for the colors: F, C
 * 		🟢 Color format: [0-255],[0-255],[0-255]
 * Allowed for metadata:
 * 🟢 Unlimited new lines
 * 🟢 Unlimited spacing
 * 🟢 Mixed order
 *
 * Grid:
 * ⭕ Must contains only the following characters: 0, 1, N, S, E, W
 * ⭕ Must be closed/surrounded by walls (char '1')
 * ⭕ Cannot contain empty lines
 * ⭕ Needs to be the last element in the file (no extra data after)
 * Allowed for grid:
 * ⭕ Spaces outside of the walls (char '1')
 *
 * If invalid grid:
 * ⭕ Clean program exit + print "Error\n" followed by detail
 * of the error
*/

#include "cub3d.h"

static bool	is_valid_texture(char *id, char *filepath, bool ret)
{
	int	fd;

	if (!ret)
		return (ret);
	if (filepath[0] == 0)
		return (put_error2(id, "No texture path provided"), false);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (put_error2(id, filepath), false);
	close(fd);
	return (true);
}

/**
 * Check that each part of the color hexa code:
 * - Only contains digits
 * - is a number in range [0,255]
 */
static bool	is_valid_color_part(char *part)
{
	int	i;

	i = 0;
	while (part[i])
	{
		if (!ft_isdigit(part[i]))
			return (false);
		i++;
	}
	if (ft_atoi(part) < 0 || ft_atoi(part) > 255)
		return (false);
	return (true);
}

/**
 * Check that the color hexa code is valid:
 * - `color` is not an empty string
 * - `color` contains only one word
 * - String is made of 3 parts and is not ending with ','
 * - `is_valid_color_part` returns `true` for each part of the color code
 */
static bool	is_valid_color(char *id, char *color, bool ret)
{
	char	**parts;
	int		i;

	if (!ret)
		return (ret);
	if (color[0] == 0)
		return (put_error2(id, "No color code provided"), false);
	if (has_more_than_one_word(color))
		return (put_error2(id, "Invalid color code"), false);
	parts = ft_split(color, ',');
	if (!parts)
		return (put_error2(ERR_FATAL_PARSING, "color allocation"), false);
	if (ft_matrix_size(parts) != 3 || color[ft_strlen(color)-1] == ',')
		return (ft_free_split(&parts), put_error2(id, "Invalid color code"),
			false);
	i = 0;
	while (parts[i])
	{
		if (!is_valid_color_part(parts[i]))
			return (ft_free_split(&parts), put_error2(id, "Invalid color code"),
				false);
		i++;
	}
	ft_free_split(&parts);
	return (true);
}

bool	is_valid_metadata(t_map *map)
{
	int	ret;

	ret = true;
	ret = is_valid_texture("NO", map->texture_no, ret);
	ret = is_valid_texture("SO", map->texture_so, ret);
	ret = is_valid_texture("EA", map->texture_ea, ret);
	ret = is_valid_texture("WE", map->texture_we, ret);
	ret = is_valid_color("C", map->color_c, ret);
	ret = is_valid_color("F", map->color_f, ret);
	return (ret);
}

bool	is_valid_grid(t_map *map)
{
	(void)map; //TODO
	return (true);
}
