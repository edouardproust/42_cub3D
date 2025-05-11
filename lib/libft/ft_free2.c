/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:54:41 by eproust           #+#    #+#             */
/*   Updated: 2025/01/19 14:58:55 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees 2 strings in a safe manner. For each string:
 * - Check that the input string is not NULL.
 * - Set the freed string to NULL.
 */
void	*ft_free2(char **s1, char **s2)
{
	ft_free(s1);
	ft_free(s2);
	return (NULL);
}
