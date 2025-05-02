#include "cub3d.h"

bool	is_metadata_parsed(t_map *map)
{
    if (map->texture_no && map->texture_so && map->texture_ea
		&& map->texture_we && map->color_c &&map->color_f)
		return (true);
	return (false);
}

static int	parse_metadata(char *line, int start, char **map_tx)
{
	int	i;

	if (line[start] != ' ')
		return (put_error("Parsing: wrong metadata format"), EXIT_FAILURE);
	//TODO Question: map is invalid if more than 1 space between id and value?
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
	start++;
	i = start;
	while (line[i] && line[i] != '\n')
		i++;
	*map_tx = ft_substr(line, start, i - start);
	if (!*map_tx)
		return (put_error("Parsing: map metadata"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
int parse_line_to_metadata(char *line, t_map *map, int ret)
{
	if (ret != EXIT_SUCCESS)
		return (ret);
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		ret = parse_metadata(line, 2, &map->texture_no);
	else if (ft_strncmp(line, "SO", 2) == 0)
		ret = parse_metadata(line, 2, &map->texture_so);
	else if (ft_strncmp(line, "EA", 2) == 0)
		ret = parse_metadata(line, 2, &map->texture_ea);
	else if (ft_strncmp(line, "WE", 2) == 0)
		ret = parse_metadata(line, 2, &map->texture_we);
	else if (ft_strncmp(line, "F", 1) == 0)
		ret = parse_metadata(line, 1, &map->color_f);
	else if (ft_strncmp(line, "C", 1) == 0)
		ret = parse_metadata(line, 1, &map->color_c);
	else if (line[0] != '\0')  // None-empty line without metadata
		return (put_error("Parsing: invalid metadata line"), EXIT_FAILURE);
	return (ret);
}