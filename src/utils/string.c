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
int	putstrnl_fd(char *str, int fd)
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

/**
 * Check if a string is empty or contains only space chars.
 *
 * @note A space is defined by ft_isspace.
 */
bool	is_blank_str(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

/**
 * Counts the number of space characters (based on ft_isspace)
 * in a string segment.
 * Can operate either left-to-right (LTR) or right-to-left (RTL).
 *
 * @param str The input string to analyze
 * @param start The starting index (inclusive) of the segment to check
 * @param end The ending index (exclusive) of the segment to check
 * @param rtl Direction flag:
 * - false = count spaces from start moving forward (LTR)
 * - true  = count spaces from end-1 moving backward (RTL)
 * @return The number of consecutive space characters found:
 * - From start position in LTR mode
 * - Before end position in RTL mode
 * Returns 0 if no spaces are found at the starting position
 */
int	count_space_chars(char *str, int start, int end, bool rtl)
{
	int	count;

	count = 0;
	if (!str || start < 0 || end <= start)
		return (0);
	if (!rtl)
	{
		while (start + count < end && str[start + count]
			&& ft_isspace(str[start + count]))
			count++;
	}
	else
	{
		while (end - count > start && ft_isspace(str[end - count - 1]))
			count++;
	}
	return (count);
}
