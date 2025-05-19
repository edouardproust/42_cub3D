#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include "config.h"
# include <stdio.h> // printf
# include <stdbool.h> // bool, true, false
# include <errno.h> // errno
# include <string.h> // strerror
# include <fcntl.h> // open
# include <limits.h> // INT_MAX
# include <math.h> // sin, cos, M_PI

/****************************************/
/* Macros and Enums                     */
/****************************************/

/* Errors prefix */
# define E_PARSING "Parsing"
# define E_FATAL_PARSING "Fatal: Parsing"

/****************************************/
/* Structs and Typedefs                 */
/****************************************/

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

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
	t_cell		start_pos;
	char		start_dir;
}	t_map;

typedef struct s_keymap
{
	keys_t		mlx;
	t_keys		value;
}	t_keymap;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*minimap;
	mlx_image_t	*mm_player;
	mlx_image_t	*mm_dir;
	t_point		pos;
	t_point		dir;
	t_point		camera_plane;
	double		last_frame;
	bool		key_states[KEY_COUNT];
	double		player_rot;
	int32_t		win_width;
	int32_t		win_height;
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
void		loop_hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		close_hook(void *param);
void		resize_hook(int32_t width, int32_t height, void *param);

/* Keymapping */
t_keys		mlx_key_to_enum(keys_t mlx_key);
void		handle_special_keys(mlx_key_data_t keydata, t_game *game);
/* Minimap */
void		draw_minimap(t_game *game);

/******** Player ********/
void		move_player(t_game *game, double move_speed);
void		rotate_player(t_game *game, double delta_time);

/******** Utils ********/
/* MLX */
void		clear_image_pixels(mlx_image_t *img);
mlx_image_t	*texture_to_window(t_game *g, const char *img_path, int width,
				t_point pos);
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
