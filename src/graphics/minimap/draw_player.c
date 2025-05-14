#include "cub3d.h"
/**
 * Draws a directional line from the player's position on the minimap, indicating
 * their facing direction.
 * 
 * @param game   Pointer to the game structure.
 * @param px     Player's X position on the minimap.
 * @param py     Player's Y position on the minimap.
 * 
 * 1. Calculates the endpoint using trigonometry:
 *  - cos(game->player_rot) for horizontal direction (X-axis).
 *  - sin(game->player_rot) for vertical direction (Y-axis).
 *  - Length: PLAYER_RADIUS * 2 (doubled for visibility).
 * 2. Adjusts dx and dy toward the endpoint, drawing pixels along the way.
 * 
 * Notes:
 * - Uses cos/sin to convert rotation angle to direction.
 * - Y-axis is inverted (- sin(...)), as screen coordinates increase downward.
 */
void	draw_direction_line(t_game *game, int px, int py)
{
	int	dx;
	int	dy;
	int	end_x;
	int	end_y;

	end_x = px + (int)(cos(game->player_rot) * (PLAYER_RADIUS * 2));
	end_y = py - (int)(sin(game->player_rot) * (PLAYER_RADIUS * 2));
	dx = px;
	dy = py;
	while (dx != end_x || dy != end_y)
	{
		mlx_put_pixel(game->minimap, dx, dy, 0x00FF00FF);
		if (dx < end_x)
			dx++;
		else if (dx > end_x)
			dx--;
		if (dy < end_y)
			dy++;
		else if (dy > end_y)
			dy--;
	}
}

/**
 * Draws the player as a filled circle on the minimap.
 * 
 * @param game   Pointer to the game structure.
 * 
 * 1. Converts player's map coordinates to minimap pixels using MN_SCALE.
 * 2. Iterates over a square grid around the player's position (r=PLAYER_RADIUS).
 * 3. Uses the circle equation (dx^2 + dy^2 ≤ radius^2) to draw filled pixels.
 * 4. Draws the direction line afterward.
 * 
 * Notes:
 * - MN_SCALE converts map grid units to pixels (eg, 20 pixels per grid cell).
 * - PLAYER_RADIUS defines the circle size (eg, 3 pixels).
 */
void	draw_player_circle(t_game *game)
{
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = (int)(game->player_x * MN_SCALE);
	py = (int)(game->player_y * MN_SCALE);
	dy = -PLAYER_RADIUS;
	while (dy <= PLAYER_RADIUS)
	{
		dx = -PLAYER_RADIUS;
		while (dx <= PLAYER_RADIUS)
		{
			if (dx * dx + dy * dy <= PLAYER_RADIUS * PLAYER_RADIUS)
				mlx_put_pixel(game->minimap, px + dx, py + dy, 0xFF0000FF);
			dx++;
		}
		dy++;
	}
	draw_direction_line(game, px, py);
}
