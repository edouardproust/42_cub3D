#include "cub3d.h"

void print_rays_length(t_game *g)
{
	t_point		ray_dir;
	t_ray_dist	delta_dist; // length of the ray to cross one cell along the X-axis or Y-axis
	t_ray_dist	side_dist; // length of ray from current position to next X-side or Y-side
	t_cell		cell; // The cell coordinates ray is currently crossing
	t_cell		step; // The direction to the next cell the ray will be crossing
	double		camera_x;
	double		perp_wall_dist;
	int			x;
	bool		hit;
	t_side		side;

	x = 0;
	while (x < SCREEN_WIDTH_PX)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)SCREEN_WIDTH_PX - 1;
		ray_dir.x = g->dir.x + g->plane.x * camera_x;
		ray_dir.y = g->dir.y + g->plane.y * camera_x;

		//which cell of the map we're in
		cell.x = (int)g->pos.x;
		cell.y = (int)g->pos.y;

		// Calculate delta_dist (length of the ray if we move of 1 cell on x, or of 1 cell on y)
		delta_dist.x = INFINITY;
		delta_dist.y = INFINITY;
		if (ray_dir.x != 0)
			delta_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		if (ray_dir.y != 0)
			delta_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));

		//calculate step and initial side_dist
		if(ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (g->pos.x - cell.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (cell.x + 1.0 - g->pos.x) * delta_dist.x;
		}
		if(ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (g->pos.y - cell.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (cell.y + 1.0 - g->pos.y) * delta_dist.y;
		}

		//perform DDA
		hit = false;
		while(!hit)
		{
			//jump to next map cell, either in x-direction, or in y-direction
			if(side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				cell.x += step.x;
				side = WEST;
				if (ray_dir.x > 0)
					side = EAST;
			}
			else
			{
				side_dist.y += delta_dist.y;
				cell.y += step.y;
				side = NORTH;
				if (ray_dir.y > 0)
					side = SOUTH;
			}

			//Check if ray has hit a wall
			if(g->map->grid[cell.y][cell.x] > 0)
				hit = true;
		}
		print_ray(g->pos, side_dist);

		// increment x
		x++;
	}
}
