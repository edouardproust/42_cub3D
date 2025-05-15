#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int32_t main(void)
{
    // Force software rendering for WSL2
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);

    mlx_t* mlx = mlx_init(800, 600, "Test", true);
    if (!mlx)
    {
        fprintf(stderr, "MLX42 failed to initialize!\n");
        return EXIT_FAILURE;
    }

    // Create a white image to test rendering
    mlx_image_t* img = mlx_new_image(mlx, 800, 600);
    if (!img)
    {
        fprintf(stderr, "Failed to create image!\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    memset(img->pixels, 255, img->width * img->height * sizeof(int32_t)); // Fill with white
    mlx_image_to_window(mlx, img, 0, 0);

    mlx_loop(mlx);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
