#include "cub3d.h"

void	clear_image_pixels(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}

