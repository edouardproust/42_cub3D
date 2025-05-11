#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
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
static void	file_read_and_parse(char *filepath, t_game *g)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_game(filepath, g);
	ret = EXIT_SUCCESS;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_metadata_parsed(g->map))
			ret = parse_line_to_metadata(line, g->map, ret);
		else
			ret = parse_line_to_grid(line, g->map, ret);
		free(line);
	}
	close(fd);
	if (ret == EXIT_FAILURE)
		exit_game(NULL, g);
}

void	map_parse_and_check(char *filepath, t_game *g)
{
	if (!has_valid_extension(filepath, ".cub"))
		exit_game("Map file must have a .cub extension", g);
	file_read_and_parse(filepath, g);
	check_metadata_lines(g);
	check_grid_lines(g);
	trim_empty_lines_after_grid(g);
	uniformize_grid_margins(g);
	check_grid_is_closed(g);
}
