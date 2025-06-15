/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:08:45 by eproust           #+#    #+#             */
/*   Updated: 2024/12/16 14:32:13 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* Window Settings */
# define WIDTH 			1024	/* Main window width in pixels */
# define HEIGHT			640		/* Main window height in pixels */

/* Player Settings */
# define MOVE_SPEED 	5.0		/* Base movement speed (units/second) */
# define ROT_SPEED		3.0		/* Rotation speed (radians/second) */

/* 3D Rendering Settings */
# define COLOR_MODE		false
# define FISHEYE_EFFECT	false
# define FOV_FACTOR		0.66
# define WALL_COLOR_NO	0xFF00FFFF	/* magenta */
# define WALL_COLOR_SO	0x00FFFFFF	/* cyan */
# define WALL_COLOR_EA	0xFFFF00FF	/* yellow */
# define WALL_COLOR_WE	0x00FF00FF	/* green */

/* Keyboard Settings */
typedef enum e_keys
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ESC,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_COUNT
}	t_keys;

#endif
