#include "cub3d.h"

static void	init_game_vectors(t_game *g)
{
	g->dir.x = 0;
	g->dir.y = 0;
	g->camera_plane.x = 0;
	g->camera_plane.y = 0;
	if (g->map->start_dir == 'N')
	{
		g->dir.y = -1;
		g->camera_plane.x = FOV_FACTOR;
	}
	else if (g->map->start_dir == 'S')
	{
		g->dir.y = 1;
		g->camera_plane.x = -FOV_FACTOR;
	}
	else if (g->map->start_dir == 'W')
	{
		g->dir.x = -1;
		g->camera_plane.y = -FOV_FACTOR;
	}
	else if (g->map->start_dir == 'E')
	{
		g->dir.x = 1;
		g->camera_plane.y = FOV_FACTOR;
	}
}

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
	g->pos.x = g->map->start_pos.x + 0.5;
	g->pos.y = g->map->start_pos.y + 0.5;
	g->win_height = HEIGHT;
	g->win_width = WIDTH;
	init_game_vectors(g);
	init_mlx(g);
	cast_rays(g);
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
