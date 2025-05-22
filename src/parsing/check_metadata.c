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
static uint32_t	check_color_and_parse_rgb(char **parts, char *id, t_game *g)
{
	int	i;
	int	j;
	int	rgb[3];

	i = -1;
	while (parts[++i])
	{
		j = -1;
		while (parts[i][++j])
		{
			if (!ft_isdigit(parts[i][j]))
			{
				ft_free_split(&parts);
				exit_game3(E_PARSING, id, "Color must be digits only", g);
			}
		}
		rgb[i] = ft_atoi(parts[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_free_split(&parts);
			exit_game3(E_PARSING, id, "Color values must be 0-255", g);
		}
	}
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}

/**
 * Check that the color hexa code is valid:
 * - `color` is not an empty string
 * - `color` contains only one word
 * - String is made of 3 parts and is not ending with ','
 * - `is_valid_color_part` returns `true` for each part of the color code
 */
static void	check_color(char *id, t_color *color, t_game *g)
{
	char	**parts;

	if (is_blank_str(color->str))
		exit_game3(E_PARSING, id, "No color code provided", g);
	if (has_more_than_one_word(color->str))
		exit_game3(E_PARSING, id, "Invalid color format: expected R,G,B", g);
	parts = ft_split(color->str, ',');
	if (!parts)
		exit_game2(E_FATAL_PARSING, "Malloc for color parsing", g);
	if (ft_matrix_size(parts) != 3
		|| color->str[ft_strlen(color->str) - 1] == ',')
	{
		ft_free_split(&parts);
		exit_game3(E_PARSING, id, "Color must be in R,G,B format", g);
	}
	color->rgb = check_color_and_parse_rgb(parts, id, g);
	ft_free_split(&parts);
}

void	check_metadata_lines(t_game *g)
{
	check_texture("NO", g->map->texture_no, g);
	check_texture("SO", g->map->texture_so, g);
	check_texture("EA", g->map->texture_ea, g);
	check_texture("WE", g->map->texture_we, g);
	check_color("C", &g->map->color_c, g);
	check_color("F", &g->map->color_f, g);
}
