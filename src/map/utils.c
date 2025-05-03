#include "cub3d.h"

/**
 * Check the file extension.
 *
 * @param path The path of the file to check
 * @param ext The extension to check (must include the dot. eg ".jpg")
 * @return `true` if `path` ends by `ext`, `false` otherwise.
 */
bool	has_valid_extension(char *path, char *ext)
{
	int		ext_len;
	char	*dot_ptr;
	int		i;

	dot_ptr = ft_strrchr(path, '.');
	if (!dot_ptr)
		return (false);
	else
	{
		ext_len = ft_strlen(ext);
		i = 0;
		while (i <= ext_len)
		{
			if (*(dot_ptr + i) != ext[i])
				return (false);
			i++;
		}
	}
	return (true);
}

/**
 * Check if a map line is empty (contains nothing or only spaces).
 */
bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

/**
 * Skips generic whitespace in a string.
 *
 * @return New position after skipped chars.
 */
int	skip_whitespaces(char *str, int start)
{
	while (str[start] && ft_isspace(str[start]))
		start++;
	return (start);
}

/**
 * Checks if there is non-whitespace content after the first space
 * @param str Input string to check (may contain \n at end)
 * @return true if non-whitespace content exists after first space group,
 *         false otherwise (including NULL or single-word strings)
 */
bool	has_more_than_one_word(char *str)
{
	if (!str)
		return (false);
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (true);
	return (false);
}
