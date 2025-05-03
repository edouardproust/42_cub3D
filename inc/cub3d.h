#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h> // printf
# include <stdbool.h> // bool, true, false
# include <errno.h> // errno
# include <string.h> // strerror
# include <fcntl.h> // open

/****************************************/
/* Macros and Enums                     */
/****************************************/

/* Errors prefix */
# define ERR_PARSING "Parsing"
# define ERR_FATAL_PARSING "Fatal: Parsing"

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE
}	t_direction;

/****************************************/
/* Structs and Typedefs                 */
/****************************************/

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char		*texture_no;
	char		*texture_so;
	char		*texture_ea;
	char		*texture_we;
	char		*color_c;
	char		*color_f;
	char		**grid;
	int			grid_width;
	int			grid_height;
	t_point		player_pos;
	t_direction	player_dir;
}	t_map;

typedef struct t_data
{
	t_map	*map;
}	t_data;

/****************************************/
/* Functions                            */
/****************************************/

/* Parsing */
t_map		*map_parse_and_validate(char *filepath);
bool		is_metadata_parsed(t_map *map);
int			parse_line_to_metadata(char *line, t_map *map, int ret);
int			parse_line_to_grid(char *line, t_map *map, int ret);
bool		is_valid_metadata(t_map *map);
bool		is_valid_grid(t_map *map);
bool		has_valid_extension(char *path, char *ext);
bool		is_empty_line(char *line);
int			skip_whitespaces(char *line, int start);
bool		has_more_than_one_word(char *str);

/* Utils */
void		put_error(char *str);
void		put_error2(char *s1, char *s2);
void		put_error3(char *s1, char *s2, char *s3);
void		error_exit(char *msg);
void		free_map(t_map *map);
void		free_data(t_data **d);
int			ft_putstrnl_fd(char *str, int fd);

// DEBUG Remove the function below
void		debug_parsed_map(t_map *map);

#endif