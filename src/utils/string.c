#include "cub3d.h"

/**
 * Writes a string to the given file descriptor until newline or null terminator.
 *
 * @param str The string to write (NULL-terminated)
 * @param fd  The file descriptor to write to
 * @return -1 if str is NULL, no explicit return otherwise
 * @note Stops writing when encountering newline or end of string
 *       Each character is written individually
 */
int	ft_putstrnl_fd(char *str, int fd)
{
	int	len;

	if (!str)
		return (-1);
	len = 0;
	while (*str)
	{
		if (*str == '\n')
			break ;
		len += write(fd, str++, 1);
	}
	return (len);
}
