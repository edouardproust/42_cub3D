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
# include <math.h>

/****************************************/
/* Macros and Enums                     */
/****************************************/

/* Errors prefix */
# define E_PARSING "Parsing"
# define E_FATAL_PARSING "Fatal: Parsing"

/* Sizes */
# define WIDTH 800
# define HEIGHT	600
# define MN_SCALE 20
# define MN_X 10
# define MN_Y 10

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
	int			grid_cols;
	int			grid_rows;
	t_point		player_pos;
	char		player_dir;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*minimap;
	int			minimap_scale;
	double     	player_x;
	double      player_y;
	bool        key_w;
	bool        key_a;
	bool        key_s;
	bool        key_d;
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
void		set_map_player(t_map *map, int x, int y, char dir);

/******** Graphics ********/
void		init_mlx(t_game *game);
/* Hooks */
void		key_hook(mlx_key_data_t keydata, void *param);
void		close_hook(void *param);
/* Minimap */
void		draw_minimap_grid(t_game *game);
void		draw_player_circle(t_game *game);
void		render_minimap(void *param);

/******** Player ********/

void		update_movement(t_game *game, double move_speed);

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
