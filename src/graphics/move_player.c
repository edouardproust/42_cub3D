#include "cub3d.h"

static bool	calc_new_player_pos(t_point	*new_pos, t_game *g, double move_speed)
{
	new_pos->x = g->pos.x;
	new_pos->y = g->pos.y;
	if (g->key_states[KEY_W] || g->key_states[KEY_UP])
	{
		new_pos->x = g->pos.x + g->dir.x * move_speed;
		new_pos->y = g->pos.y + g->dir.y * move_speed;
	}
	if (g->key_states[KEY_S] || g->key_states[KEY_DOWN])
	{
		new_pos->x = g->pos.x - g->dir.x * move_speed;
		new_pos->y = g->pos.y - g->dir.y * move_speed;
	}
	if (g->key_states[KEY_A])
	{
		new_pos->x = g->pos.x + g->dir.y * move_speed;
		new_pos->y = g->pos.y - g->dir.x * move_speed;
	}
	if (g->key_states[KEY_D])
	{
		new_pos->x = g->pos.x - g->dir.y * move_speed;
		new_pos->y = g->pos.y + g->dir.x * move_speed;
	}
	return ((new_pos->x != g->pos.x) || (new_pos->y != g->pos.y));
}

void	update_minimap_player_sprite(t_game *g)
{
	int	x;
	int	y;

	x = g->pos.x * MM_SCALE + g->minimap->instances[0].x;
	y = g->pos.y * MM_SCALE + g->minimap->instances[0].y;
	g->mm_player->instances[0].x = x - g->mm_player->width / 2;
	g->mm_player->instances[0].y = y - g->mm_player->height / 2;
}

void	move_player(t_game *g, double delta_time)
{
	double	move_speed;
	t_point	new_pos;

	move_speed = MOVE_SPEED * delta_time;
	if (calc_new_player_pos(&new_pos, g, move_speed))
	{
		if (g->map->grid[(int)g->pos.y][(int)new_pos.x] != '1')
			g->pos.x = new_pos.x;
		if (g->map->grid[(int)new_pos.y][(int)g->pos.x] != '1')
			g->pos.y = new_pos.y;
		update_minimap_player_sprite(g);
	}
}
