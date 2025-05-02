#include "cub3d.h"

static bool	is_valid_texture(char *filepath, bool ret)
{
	int	fd;

	if (!ret)
		return (ret);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (put_error(filepath), false);
	close(fd);
	return (true);
}

static bool	is_valid_color(char *color, bool ret)
{
	char	**parts;
	int		i;
	int		j;

	if (!ret)
		return (ret);
	if (has_content_after_space(color))
		return (put_error2(color, "Invalid color code"), false);
	parts = ft_split(color, ',');
	//if (!parts) // TODO
	if (ft_matrix_size(parts) != 3 || color[ft_strlen(color)-1] == ',')
		return (put_error2(color, "Invalid color code"), false);
	i = 0;
	while (parts[i])
	{
		j = 0;
		while (parts[i][j])
		{
			if (!ft_isdigit(parts[i][j]))
				return (ft_free_split(&parts),
					put_error2(color, "Invalid color code"),
					false);
			j++;
		}
		if (ft_atoi(parts[i]) < 0 || ft_atoi(parts[i]) > 255)
		{
			return (ft_free_split(&parts),
				put_error2(color, "Invalid color code"),
				false);
		}
		i++;
	}
	ft_free_split(&parts);
	return (true);
}

bool	is_valid_metadata(t_map *map)
{
	int	ret;

	ret = true;
	ret = is_valid_texture(map->texture_no, ret);
	ret = is_valid_texture(map->texture_so, ret);
	ret = is_valid_texture(map->texture_ea, ret);
	ret = is_valid_texture(map->texture_we, ret);
	ret = is_valid_color(map->color_c, ret);
	ret = is_valid_color(map->color_f, ret);
	return (ret);
}

bool	is_valid_grid(t_map *map)
{
	(void)map; //TODO
	return (true);
}

/**
 * Grid checks:
 * ⭕ Must contains only the following characters: 0, 1, N, S, E, W
 * ⭕ Must be closed/surrounded by walls (char '1')
 * ⭕ Cannot contain empty lines
 * ⭕ Needs to be the last element in the file (no extra data after)
 * ⭕ Each element of data must start by the identifier, followed by the correct information:
 * 		- check number of args, file exist, color format
 * 		- Identifier followed by texture path: NO, SO, WE, EA
 * 		- Identifiers for the colors: F, C
 * 		- Color format: [0-255],[0-255],[0-255]
 * - Allowed for map data: unlimited new lines, unlimited spacing, mixed order
 * - ALlowed for the map: spaces outside of the walls (char '1')
 * - If invalid map: clean program exit + print "Error\n" followed by detail of the error
*/