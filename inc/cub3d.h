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

typedef enum e_side
{
	NO,
	EA,
	SO,
	WE,
	DOOR_OPEN,
	DOOR_CLOSED,
	DOOR_HALF
}	t_side;

typedef enum e_door_state
{
	CLOSED,
	OPEN,
}	t_door_state;

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

typedef struct s_door
{
	int	x;
	int	y;
	int	state;
}	t_door;

typedef struct color
{
	char		*str;
	uint32_t	rgb;
}	t_color;

typedef struct s_map
{
	char			*texture_no;
	char			*texture_so;
	char			*texture_ea;
	char			*texture_we;
	char			*texture_door;
	char			*texture_door_half;
	t_color			color_c;
	t_color			color_f;
	char			**grid;
	int				grid_cols;
	int				grid_rows;
	t_cell			start_pos;
	char			start_dir;
	t_door			*doors;
	int				door_count;
}	t_map;

typedef struct s_keymap
{
	keys_t		mlx;
	t_keys		value;
}	t_keymap;

typedef struct s_game
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*mm_player;
	mlx_image_t		*mm_dir;
	t_point			pos;
	t_point			dir;
	t_point			cam_plane;
	double			last_frame;
	bool			key_states[KEY_COUNT];
	bool			minimap_visible;
	bool			mouse_captured;
	int32_t			win_width;
	int32_t			win_height;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_door;
	mlx_texture_t	*tex_door_half;
	bool			show_door_half;
	t_point			door_half_pos;
}	t_game;

typedef struct s_ray
{
	double	wall_dist; // Distance to the wall (euclydian if fisheye active)
	t_point	dir; // Ray direction
	t_side	side; // The side of the wall cube (NO, SO, EA, WE) the ray hit
	double	length_x; // Distance traveled along the x-axis until a wall is hit
	double	length_y; // Distance traveled along the y-axis until a wall is hit
	double	len_step_x; // Distance to travel to cross one cell on the x-axis
	double	len_step_y; // Distance to travel to cross one cell on the y-axis
	t_cell	cell; // Cell in the grid that the ray is currently crossing
	t_cell	cell_move; // Move to the next cell the ray will cross
	bool	wall_hit; // Indicates if the ray hit a wall
	int		top_px;
	int		bottom_px;
}	t_ray;

/****************************************/
/* Functions                            */
/****************************************/

/******** Parsing ********/
t_map			*init_map(void);
void			map_parse_and_check(char *filepath, t_game *g);
bool			is_metadata_parsed(t_map *map);
int				parse_line_to_metadata(char *line, t_map *map, int ret);
int				parse_line_to_grid(char *line, t_map *map, int ret);
void			check_metadata_lines(t_game *g);
void			check_grid_lines(t_game *g);
void			check_grid_is_closed(t_game *g);
void			init_doors(t_game *g);
bool			has_valid_extension(char *path, char *ext);
bool			has_more_than_one_word(char *str);
void			trim_empty_lines_after_grid(t_game *g);
void			uniformize_grid_margins(t_game *g);
void			set_map_player(t_map *map, int x, int y, char dir);
bool			is_valid_door_position(t_map *map, int y, int x);

/******** Graphics ********/
void			display_game(t_game *game);

/* Hooks */
void			setup_hooks(t_game *game);

/* Keymapping */
t_keys			mlx_key_to_enum(keys_t mlx_key);
void			handle_special_keys(mlx_key_data_t keydata, t_game *game);

/* Minimap */
void			display_minimap(t_game *game);
void			draw_player(t_game *g);
void			draw_minimap_doors(t_game *g);
void			toggle_doors(t_game *g);
void			update_minimap_player_sprite(t_game *g);
void			update_minimap_dir_sprite(t_game *g);

/* Raycasting */
void			cast_one_ray(t_ray *ray, double screen_px_col, t_game *g);
void			draw_view_on_screen(t_game *g);
void			perform_dda_algorythm(t_ray *ray, t_game *g);

/* Textures */
void			load_textures(t_game *g);
mlx_texture_t	*get_wall_texture(t_side side, t_game *g);
double			calc_wall_hit_position(t_ray *ray, t_game *g);
int				get_texture_horizontal(mlx_texture_t *tex, double wall_x);
void			render_textured_wall(t_ray *ray, int x, t_game *g);

/******** Player ********/
bool			move_player(t_game *game, double move_speed);
bool			rotate_player(t_game *game, double delta_time);
bool			handle_mouse_rotation(t_game *g, double delta_time);

/******** Utils ********/
/* MLX */
void			clear_image_pixels(mlx_image_t *img);
mlx_image_t		*texture_to_window(t_game *g, const char *img_path, int width,
					t_point pos);
/* Error */
void			put_error(char *str);
void			put_error2(char *s1, char *s2);
void			put_error3(char *s1, char *s2, char *s3);
/* Exit */
void			exit_game(char *msg, t_game *g);
void			exit_game2(char *msg1, char *msg2, t_game *g);
void			exit_game3(char *msg1, char *msg2, char *msg3, t_game *g);
/* Free */
void			free_map(t_map *map);
void			free_game(t_game *g);
/* String */
int				putstrnl_fd(char *str, int fd);
char			*substr_trim_nl(char *str);
bool			is_blank_str(char *str);
int				count_space_chars(char *str, int start, int end, bool rtl);
/* Char */
bool			is_grid_char(char c);
bool			is_grid_player_char(char c);

// DEBUG Remove functions below
void			debug_parsed_map(t_map *map);

#endif
