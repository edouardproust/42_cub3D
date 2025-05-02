#include "cub3d.h"

void	put_error(char *str)
{
	put_error2(str, NULL);
}

void	put_error2(char *s1, char *s2)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (errno)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	error_exit(char *msg)
{
	put_error(msg);
	exit(EXIT_FAILURE);
}