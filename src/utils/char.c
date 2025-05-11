#include "cub3d.h"

bool	is_grid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_grid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || is_grid_player_char(c));
}
