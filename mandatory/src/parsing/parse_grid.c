/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes the map grid with first line of content.
 * Allocates grid array and stores first line (trimming newline).
 *
 * @param map  Map structure to initialize
 * @param line First non-empty line of grid content (with trailing newline)
 *
 * @return EXIT_SUCCESS on successful initialization,
 *         EXIT_FAILURE if:
 *           - Grid allocation fails
 *           - Line duplication fails
 */
static int	init_grid(t_map *map, char *line)
{
	map->grid = malloc(sizeof(char *));
	if (!map->grid)
		return (put_error2(E_FATAL_PARSING, "grid init alloc"), EXIT_FAILURE);
	map->grid[0] = substr_trim_nl(line);
	if (!map->grid[0])
		return (put_error2(E_FATAL_PARSING, "grid init line alloc"),
			EXIT_FAILURE);
	map->grid_rows = 1;
	return (EXIT_SUCCESS);
}

/**
 * Adds a new line to existing grid.
 * Reallocates grid array and stores new line (trimming newline).
 *
 * @param map  Map structure with existing grid
 * @param line New line of grid content (with trailing newline)

 * @return EXIT_SUCCESS on successful addition,
 *         EXIT_FAILURE if:
 *           - Grid reallocation fails
 *           - Line duplication fails
 */
static int	add_line_to_grid(t_map *map, char *line)
{
	char	**new_grid;

	new_grid = ft_realloc(map->grid, sizeof(char *) * (map->grid_rows),
			sizeof(char *) * (map->grid_rows + 1));
	if (!new_grid)
		return (put_error2(E_FATAL_PARSING, "grid realloc"), EXIT_FAILURE);
	map->grid = new_grid;
	map->grid[map->grid_rows] = substr_trim_nl(line);
	if (!map->grid[map->grid_rows])
		return (put_error2(E_FATAL_PARSING, "grid line alloc"), EXIT_FAILURE);
	map->grid_rows++;
	return (EXIT_SUCCESS);
}

/**
 * Parses a line into the map grid structure.
 * Handles grid initialization and expansion as needed.
 *
 * @param line Current line to parse (may contain trailing newline)
 * @param map  Map structure to store grid
 * @param ret  Current return status (passed through if already failed)
 *
 * @return EXIT_SUCCESS if line was processed successfully,
 *         EXIT_FAILURE if:
 *           - Previous error (ret != EXIT_SUCCESS)
 *           - Grid initialization fails
 *           - Grid expansion fails
 *         EXIT_SUCCESS for empty lines before grid starts
 */
int	parse_line_to_grid(char *line, t_map *map, int ret)
{
	if (ret == EXIT_FAILURE)
		return (ret);
	if (!map->grid && is_blank_str(line))
		return (EXIT_SUCCESS);
	if (!map->grid && !is_blank_str(line))
		ret = init_grid(map, line);
	else if (map->grid)
		ret = add_line_to_grid(map, line);
	return (ret);
}
