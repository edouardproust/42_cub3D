#include "cub3d.h"

void	cast_rays(t_game *g)
{
	int	i;
	double	ray_len;

	i = 0;
	while (i < SCREEN_WIDTH_PX)
	{
		ray_len = get_ray_length(i, g);
		printf("DEBUG: %d: ray_len: %lf\n", i, ray_len);
		i++;
	}
}