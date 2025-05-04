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
