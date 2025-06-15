/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:26 by eproust           #+#    #+#             */
/*   Updated: 2025/06/15 17:02:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_error(char *str)
{
	put_error3(str, NULL, NULL);
}

void	put_error2(char *s1, char *s2)
{
	put_error3(s1, s2, NULL);
}

void	put_error3(char *s1, char *s2, char *s3)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	putstrnl_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		putstrnl_fd(s2, STDERR_FILENO);
	}
	if (s3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		putstrnl_fd(s3, STDERR_FILENO);
	}
	if (errno)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
