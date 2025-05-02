#include "cub3d.h"

static t_map	*init_map()
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
	map->grid_height = 0;
	map->grid_width = 0;
	return (map);
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
	char	*line;
	int		ret;

	if (!has_valid_extension(filepath, ".cub"))
		error_exit("Map file must have a .cub extension");
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		error_exit(filepath);
	map = init_map();
	ret = EXIT_SUCCESS;
	while (1) {
		line = get_next_line(fd);
		if (!line)
		   break;
		if (!is_metadata_parsed(map))
			ret = parse_line_to_metadata(line, map, ret);
		else
			ret = parse_line_to_grid(line, map, ret);
		free(line);
	}
	close(fd);
	debug_parsed_map(map); //DEBUG
	if (ret != EXIT_SUCCESS || !is_valid_metadata(map) || !is_valid_grid(map))
		(free_map(map), exit(EXIT_FAILURE));
	//grid_handle_spaces(map->grid); //TODO
	//grid_remove_trim_lines_after(map->grid) //TODO
	return (map);
}