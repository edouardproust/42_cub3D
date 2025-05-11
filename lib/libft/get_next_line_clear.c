/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_clear.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:15:14 by eproust           #+#    #+#             */
/*   Updated: 2025/01/19 15:03:17 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Safely clears get_next_line's stash by reading remaining lines.
 * Frees the current line and all subsequent lines until EOF, then closes the fd.
 *
 * @param line Current line to free (can be NULL)
 * @param fd File descriptor to clean up
 *
 * @note Ensures no memory leaks if GNL is interrupted prematurely.
 * @warning Closes the fd! Do not reuse it after calling this.
 */
void	get_next_line_clear(char *line, int fd)
{
	if (line)
		free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
}
