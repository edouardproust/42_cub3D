#include "cub3d.h"

static t_game	*init_game(char **argv)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		exit_game("Data memory allocation", NULL); //TODO
	ft_memset(g, 0, sizeof(t_game));
	g->map = init_map();
	if (!g->map)
		exit_game("Map memory allocation", g);
	map_parse_and_check(argv[1], g);
	debug_parsed_map(g->map); //DEBUG
	g->player_x = g->map->player_pos.x + 0.5;
	g->player_y = g->map->player_pos.y + 0.5;
	init_mlx(g);
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
	mlx_loop(game->mlx);
	// TODO run game based on map
	free_game(game);
	return (EXIT_SUCCESS);
}
