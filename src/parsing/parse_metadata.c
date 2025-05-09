#include "cub3d.h"

bool	is_metadata_parsed(t_map *map)
{
	if (map->texture_no && map->texture_so && map->texture_ea
		&& map->texture_we && map->color_c && map->color_f)
		return (true);
	return (false);
}

/**
 * Extract the value for the given metadata id,
 * and save it into the t_map struct.
 *
 * @note Skip spaces between id and value. //TODO verify if ok with subject
 */
static void	parse_metadata(char *id, char *line, char **map_tx, t_game *g)
{
	int	start;
	int	end;
	int	line_len;

	if (*map_tx != NULL)
		exit_game3(E_PARSING, id, "double definition", g);
	line_len = ft_strlen(line);
	start = count_space_chars(line, 0, line_len, false);
	end = count_space_chars(line, 0, line_len - 1, true);
	*map_tx = ft_substr(line, start, line_len - start - end - 1);
	if (!*map_tx)
		exit_game3(E_PARSING, id, "map metadata", g);
}

/**
 * Parses a line from .cub file into map metadata.
 * Skips leading whitespace and routes to appropriate metadata parser.
 *
 * @param line Current line to parse (may contain leading whitespace)
 * @param map  Map structure to store parsed metadata
 * @param ret  Current return status (passed through if already failed)
 *
 * @return EXIT_SUCCESS if metadata was parsed correctly,
 *         EXIT_FAILURE if:
 *           - Invalid metadata identifier
 *           - Empty line (no metadata)
 *           - Previous error (ret != EXIT_SUCCESS)
 *           - Metadata parsing fails
 */
void	parse_line_to_metadata(char *line, t_map *map, t_game *g)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_metadata("NO", line + 2, &map->texture_no, g);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_metadata("SO", line + 2, &map->texture_so, g);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_metadata("EA", line + 2, &map->texture_ea, g);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_metadata("WE", line + 2, &map->texture_we, g);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_metadata("F", line + 1, &map->color_f, g);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_metadata("C", line + 1, &map->color_c, g);
	else if (line[0] != '\0')
		exit_game3(E_PARSING, line, "invalid metadata line", g);
}
