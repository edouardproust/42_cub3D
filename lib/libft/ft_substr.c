/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:38:35 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 16:40:16 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Extracts a substring from `s` starting at index `start` (inclusive)
 * with maximum length `len`.
 *
 * @param s Source string (NULL-terminated).
 * @param start Starting index (inclusive, 0-based).
 * @param len Maximum length of substring.
 *
 * @return Newly allocated substring, or:
 *         - NULL if `s` is NULL or allocation fails
 *         - Empty string if `start` is beyond string length
 *
 * @note The substring includes characters from `s[start]` to either:
 *       - `s[start + len - 1]` (if within bounds)
 *       - End of string (whichever comes first)
 * @note Always NULL-terminates the result
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	alloc;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	alloc = s_len - start;
	if (alloc > len)
		alloc = len;
	substr = malloc (sizeof(char) * (alloc + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, alloc + 1);
	return (substr);
}

/*
#include <stdio.h>

int	main(void)
{
	char *str = "Hello, World!";
	int start = 7;
	int len = 5;

	printf("str: '%s'\n", str);
	char *substr = ft_substr(str, start, len);
	printf("substr: '%s'\n", substr);
	free(substr);

	return (0);
}
*/
