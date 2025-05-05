#include "cub3d.h"

static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_exit("Map memory allocation");
	map->texture_no = NULL;
	map->texture_so = NULL;
	map->texture_ea = NULL;
	map->texture_we = NULL;
	map->color_c = NULL;
	map->color_f = NULL;
	map->grid = NULL;
	map->grid_rows = -1;
	map->grid_cols = -1;
	map->player_pos.x = -1;
	map->player_pos.y = -1;
	map->player_dir = 0;
	return (map);
}

/**
 * Read the file using get_next_line.
 * - Start by parsing metadata. Parse grid only once all the
 * metadata has been parsed correctly.
 * - Finish reading the file but stop parsing as soon as an error
 * is encountered: `ret == false`
 */
int	file_read_and_parse(int fd, t_map *map)
{
	char	*line;
	int		ret;

	ret = EXIT_SUCCESS;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_metadata_parsed(map))
			ret = parse_line_to_metadata(line, map, ret);
		else
			ret = parse_line_to_grid(line, map, ret);
		free(line);
	}
	return (ret);
}

/**
 * Parses and validates a .cub map file.
 * Handles file opening/closing, metadata parsing, grid parsing,
 * and final validation of the complete map structure.
 *
 * @param filepath Path to the .cub map file to parse
 *
 * @return Pointer to fully parsed and validated t_map structure,
 *         or exits with error if:
 *           - Invalid file extension
 *           - File cannot be opened
 *           - Memory allocation fails
 *           - Metadata is incomplete/invalid
 *           - Grid is invalid (not surrounded by walls, etc.)
 * @note Caller is responsible for freeing the returned map.
 */
t_map	*map_parse_and_validate(char *filepath)
{
	int		fd;
	t_map	*map;
	int		ret;

	if (!has_valid_extension(filepath, ".cub"))
		error_exit("Map file must have a .cub extension");
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		error_exit(filepath);
	map = init_map();
	ret = file_read_and_parse(fd, map);
	close(fd);
	if (ret != EXIT_SUCCESS || !is_valid_metadata(map)
		|| !is_valid_grid(map))
		return (free_map(map), NULL);
	if (trim_empty_lines_after_grid(map) != EXIT_SUCCESS)
		return (free_map(map), NULL);
	if (uniformize_grid_margins(map) != EXIT_SUCCESS)
		return (free_map(map), NULL);
	if (!is_grid_closed(map))
		return (free_map(map), NULL);
	return (map);
}
