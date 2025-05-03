#include "cub3d.h"

static void	init_data(t_data **d, t_map *map)
{
	*d = malloc(sizeof(t_data));
	if (!*d)
		error_exit("Data memory allocation");
	(*d)->map = map;
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map;

	if (argc != 2)
		error_exit("Wrong number of arguments. Usage: ./cub3D <map_file.cub>");
	map = map_parse_and_validate(argv[1]);
	init_data(&data, map);
	// TODO display window
	// TODO run game based on map
	free_data(&data);
	return (EXIT_SUCCESS);
}
