#include "cub3d.h"

/**
 * Gets metadata specifications array.
 *
 * @note Static array initialized with current map targets
 */
t_metadata *get_metadata_specs(t_map *map)
{
    static t_metadata meta[] = {
	{"NO", TEXTURE, NULL},
	{"SO", TEXTURE, NULL},
	{"EA", TEXTURE, NULL},
	{"WE", TEXTURE, NULL},
	{"F", COLOR, NULL},
	{"C", COLOR, NULL},
	{NULL, NONE, NULL}
    };
	meta[0].target = map->texture_no;
	meta[1].target = map->texture_so;
	meta[2].target = map->texture_ea;
	meta[3].target = map->texture_we;
	meta[4].target = map->color_f;
	meta[5].target = map->color_c;
    return (meta);
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
	t_metadata	*m;
	size_t		id_len;

	if (ret != EXIT_SUCCESS || !line || !map)
		return (ret);
	while (ft_isspace(*line))
		line++;
	if (*line == '\0')
		return (EXIT_SUCCESS);
	m = get_metadata_specs(map);
	while (m->id)
	{
		id_len = ft_strlen(m->id);
		printf("DEBUG: '%s' + %ld : %d\n", m->id, id_len, ft_strncmp(line, m->id, id_len));
		if (ft_strncmp(line, m->id, id_len) == 0)
			return parse_metadata(line, id_len, &m->target);
		m++;
	}
	return (put_error("Parsing: missing metadata"), EXIT_FAILURE);
}

bool	is_metadata_parsed(t_map *map)
{
    if (map->texture_no && map->texture_so && map->texture_ea
		&& map->texture_we && map->color_c &&map->color_f)
		return (true);
	return (false);
}