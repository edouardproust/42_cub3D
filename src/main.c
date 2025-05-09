#include "cub3d.h"

static t_game	*init_game(char **argv)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		exit_game("Data memory allocation", NULL); //TODO
	g->map = NULL;
	g->map = map_parse_and_validate(argv[1], g);
	if (!g->map)
		exit_game(NULL, g);
	debug_parsed_map(g->map); //DEBUG
	return (g);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		put_error("Wrong number of arguments. Usage: ./cub3D <map_file.cub>");
		return (EXIT_FAILURE);
	}
	game = init_game(argv);
	// TODO display window
	// TODO run game based on map
	free_game(game);
	return (EXIT_SUCCESS);
}
