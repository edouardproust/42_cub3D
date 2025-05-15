#include "cub3d.h"

static t_cell	calc_step(t_point start, t_point end)
{
    t_cell step;

	if (start.x < end.x)
	step.x = 1;
	else
		step.x = -1;
	if (start.y < end.y)
		step.y = 1;
	else
		step.y = -1;
	return (step);
}

/**
 * Draws a directional line from player's position using Bresenham's algorithm
 *
 * @param g   Pointer to g structure
 * @param px     Player's X position on minimap
 * @param py     Player's Y position on minimap
 */
void draw_direction_line(t_game *g, t_point start)
{
 	t_point end;	// Final coordinates of the line
    int x;			// Current X position while drawing the line
    int y;			// Current Y position while drawing the line
    int dx;			// Absolute X distance between start and end points
    int dy;			// Absolute (negative) Y distance between start and end points
	t_cell step;	// Step direction {x, y}
    int err;		// Error term used to determine next step
    int e2;			// Temporary variable for error calculation

	end.x = start.x + (int)(cos(g->player_rot) * (PLAYER_RADIUS * 5));
	end.y = start.y - (int)(sin(g->player_rot) * (PLAYER_RADIUS * 5));
	x = start.x;
	y = start.y;
	dx = fabs(end.x - start.x);
	dy = -fabs(end.y - start.y);
	step = calc_step(start, end);
	err = dx + dy;
	while (1)
	{
		if (x >= 0 && x < (int)g->minimap->width &&
			y >= 0 && y < (int)g->minimap->height)
			mlx_put_pixel(g->minimap, x, y, MN_COLOR_DIR);
		if (x == end.x && y == end.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
			(err += dy, x += step.x);
		if (e2 <= dx)
			(err += dx, y += step.y);
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
	t_point	start;
	int	dx;
	int	dy;

	start.x = game->pos.x * MN_SCALE;
	start.y = game->pos.y * MN_SCALE;
	dy = -PLAYER_RADIUS;
	while (dy <= PLAYER_RADIUS)
	{
		dx = -PLAYER_RADIUS;
		while (dx <= PLAYER_RADIUS)
		{
			if (dx * dx + dy * dy <= PLAYER_RADIUS * PLAYER_RADIUS)
				mlx_put_pixel(game->minimap, start.x + dx, start.y + dy, MN_COLOR_PLAYR);
			dx++;
		}
		dy++;
	}
	draw_direction_line(game, start);
}
