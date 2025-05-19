#include "cub3d.h"

void	clear_image_pixels(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}

/**
 * Display a sprite to the window and center it on `pos` point.
 */
mlx_image_t	*texture_to_window(t_game *g, const char *img_path, int width,
	t_point pos)
{
	mlx_texture_t	*tx;
	mlx_image_t		*img;

	tx = mlx_load_png(img_path);
	if (!tx)
		exit_game("MLX42: Invalid texture", g);
	img = mlx_texture_to_image(g->mlx, tx);
	if (!img)
		exit_game("Image creation failed", g);
	mlx_resize_image(img, width, img->height * width / img->width);
	mlx_image_to_window(g->mlx, img, pos.x - img->width / 2,
		pos.y - img->height / 2);
	mlx_delete_texture(tx);
	return (img);
}
