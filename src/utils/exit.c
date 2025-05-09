#include "cub3d.h"

void	exit_game(char *msg, t_game *g)
{
	put_error(msg);
	free_game(g);
	exit(EXIT_FAILURE);
}

void	exit_game2(char *msg1, char *msg2, t_game *g)
{
	put_error2(msg1, msg2);
	free_game(g);
	exit(EXIT_FAILURE);
}

void	exit_game3(char *msg1, char *msg2, char *msg3, t_game *g)
{
	put_error3(msg1, msg2, msg3);
	free_game(g);
	exit(EXIT_FAILURE);
}
