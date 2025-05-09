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
 * If error:
 * 🟠 Clean program exit + print "Error\n" followed by detail
 * of the error
*/

#include "cub3d.h"

static void	check_texture(char *id, char *filepath, t_game *g)
{
	int	fd;

	if (is_blank_str(filepath))
		exit_game3(E_PARSING, id, "No texture path provided", g);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_game2(E_PARSING, filepath, g);
	close(fd);
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
static void	check_color(char *id, char *color, t_game *g)
{
	char	**parts;
	int		i;
	char	*glob_err;

	glob_err = "Invalid color code";
	if (is_blank_str(color))
		exit_game3(E_PARSING, id, "No color code provided", g);
	if (has_more_than_one_word(color))
		exit_game3(E_PARSING, id, glob_err, g);
	parts = ft_split(color, ',');
	if (!parts)
		exit_game2(E_FATAL_PARSING, "color allocation", g);
	if (ft_matrix_size(parts) != 3 || color[ft_strlen(color)-1] == ',')
		(ft_free_split(&parts), exit_game3(E_PARSING, id, glob_err, g));
	i = 0;
	while (parts[i])
	{
		if (!is_valid_color_part(parts[i]))
			(ft_free_split(&parts), exit_game3(E_PARSING, id, glob_err, g));
		i++;
	}
	ft_free_split(&parts);
}

void	check_metadata_lines(t_game *g)
{
	check_texture("NO", g->map->texture_no, g);
	check_texture("SO", g->map->texture_so, g);
	check_texture("EA", g->map->texture_ea, g);
	check_texture("WE", g->map->texture_we, g);
	check_color("C", g->map->color_c, g);
	check_color("F", g->map->color_f, g);
}
