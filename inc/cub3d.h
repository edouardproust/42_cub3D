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
# define FISHEYE_EFFECT false

typedef enum s_side
{
	NO,
	EA,
	SO,
	WE,
} t_side;


/****************************************/
/* Structs and Typedefs                 */
/****************************************/

// Stores floating-point coordinates (can be located anywhere within the grid)
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

// Stores integer coordinates (representing positions on grid intersections)
typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

// Stores the distances along the x and y axes for a ray's movement through the grid
typedef struct s_ray
{
	t_point	dir; // Ray direction
	t_side	side; // The side of the wall cube (NO, SO, EA, WE) the ray hit
	double	length_x; // Distance traveled along the x-axis until a wall is hit
	double	length_y; // Distance traveled along the y-axis until a wall is hit
	double	len_step_x; // Distance to travel to cross one cell on the x-axis
	double	len_step_y; // Distance to travel to cross one cell on the y-axis
	t_cell	cell; // Cell in the grid that the ray is currently crossing
	t_cell	cell_move; // Move to the next cell the ray will cross
	bool	wall_hit; // Indicates if the ray hit a wall
} t_ray;


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
	t_cell	dir;
	t_point	camera_plane;
}	t_game;

/****************************************/
/* Functions                            */
/****************************************/

/******** Parsing ********/
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

/******** Raycasting ********/
void		cast_rays(t_game *g);
double		get_ray_length(double screen_px_col, t_game *g);

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
