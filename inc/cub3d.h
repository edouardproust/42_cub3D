#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include <stdio.h> // printf
# include <stdbool.h> // bool, true, false
# include <errno.h> // errno
# include <string.h> // strerror
# include <fcntl.h> // open
# include <limits.h> // INT_MAX
# include <math.h> // INFINITY

/****************************************/
/* Macros and Enums                     */
/****************************************/

/* Errors prefix */
# define E_PARSING "Parsing"
# define E_FATAL_PARSING "Fatal: Parsing"

# define SCREEN_WIDTH_PX	640
# define SCREEN_HEIGHT_PX 480
# define FOV_FACTOR 0.66

typedef enum s_side
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
} t_side;


/****************************************/
/* Structs and Typedefs                 */
/****************************************/

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray_dist
{
	double	x;
	double	y;
}	t_ray_dist;

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

typedef struct s_map
{
	char	*texture_no;
	char	*texture_so;
	char	*texture_ea;
	char	*texture_we;
	char	*color_c;
	char	*color_f;
	char	**grid;
	int		grid_cols;
	int		grid_rows;
	t_point	start_pos;
	char	start_dir;
}	t_map;

typedef struct s_game
{
	t_map	*map;
	t_point	pos;
	t_point	dir;
	t_point	plane;
}	t_game;

/****************************************/
/* Functions                            */
/****************************************/

/* Parsing */
t_map		*init_map(void);
void		map_parse_and_check(char *filepath, t_game *g);
bool		is_metadata_parsed(t_map *map);
int			parse_line_to_metadata(char *line, t_map *map, int ret);
int			parse_line_to_grid(char *line, t_map *map, int ret);
void		check_metadata_lines(t_game *g);
void		check_grid_lines(t_game *g);
void		check_grid_is_closed(t_game *g);
bool		has_valid_extension(char *path, char *ext);
bool		has_more_than_one_word(char *str);
void		trim_empty_lines_after_grid(t_game *g);
void		uniformize_grid_margins(t_game *g);
void		update_player(t_map *map, int x, int y, char dir);

/******** Utils ********/
/* Error */
void		put_error(char *str);
void		put_error2(char *s1, char *s2);
void		put_error3(char *s1, char *s2, char *s3);
/* Exit */
void		exit_game(char *msg, t_game *g);
void		exit_game2(char *msg1, char *msg2, t_game *g);
void		exit_game3(char *msg1, char *msg2, char *msg3, t_game *g);
/* Free */
void		free_map(t_map *map);
void		free_game(t_game *g);
/* String */
int			putstrnl_fd(char *str, int fd);
char		*substr_trim_nl(char *str);
bool		is_blank_str(char *str);
int			count_space_chars(char *str, int start, int end, bool rtl);
/* Char */
bool		is_grid_char(char c);
bool		is_grid_player_char(char c);

// DEBUG Remove functions below
void		debug_parsed_map(t_map *map);

#endif
