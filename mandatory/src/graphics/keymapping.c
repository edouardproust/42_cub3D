#include "cub3d.h"
/**
 * Provides key mapping between MLX keycodes and engine key enums.
 * 
 * @return Static keymap array
 */
static t_keymap	*get_keymap(void)
{
	static t_keymap	keymap[] = {
	{MLX_KEY_W, KEY_W},
	{MLX_KEY_A, KEY_A},
	{MLX_KEY_S, KEY_S},
	{MLX_KEY_D, KEY_D},
	{MLX_KEY_UP, KEY_UP},
	{MLX_KEY_DOWN, KEY_DOWN},
	{MLX_KEY_LEFT, KEY_LEFT},
	{MLX_KEY_RIGHT, KEY_RIGHT},
	{MLX_KEY_ESCAPE, KEY_ESC},
	{0, KEY_COUNT}
	};

	return (keymap);
}

/**
 * Converts MLX keycode to engine-specific key enum.
 * 
 * @param mlx_key MLX keycode
 * @return Mapped KEY_* enum or KEY_COUNT if unmapped
 */
t_keys	mlx_key_to_enum(keys_t mlx_key)
{
	t_keymap	*keymap;
	size_t		i;

	keymap = get_keymap();
	i = 0;
	while (keymap[i].mlx != 0)
	{
		if (keymap[i].mlx == mlx_key)
			return (keymap[i].value);
		i++;
	}
	return (KEY_COUNT);
}

/**
 * Handles special key actions:
 * - ESC: Close window
 * 
 * @param keydata MLX key event data
 * @param game Game context pointer
 */
void	handle_special_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}
