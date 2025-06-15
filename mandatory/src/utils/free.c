/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_grid(char **grid, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(grid[i++]);
	free(grid);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free(map->texture_no);
	free(map->texture_so);
	free(map->texture_ea);
	free(map->texture_we);
	free(map->color_c.str);
	free(map->color_f.str);
	free_grid(map->grid, map->grid_rows);
	free(map);
}

static void	free_textures(t_game *g)
{
	if (g->tex_no)
		mlx_delete_texture(g->tex_no);
	if (g->tex_so)
		mlx_delete_texture(g->tex_so);
	if (g->tex_ea)
		mlx_delete_texture(g->tex_ea);
	if (g->tex_we)
		mlx_delete_texture(g->tex_we);
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx)
	{
		if (g->screen)
			mlx_delete_image(g->mlx, g->screen);
		free_textures(g);
		mlx_terminate(g->mlx);
	}
	free_map(g->map);
	free(g);
}
