NAME = ../cub3D_bonus

# ************************************
# Sources                            *
# ************************************

C_DIR = src

C_FILES = debug.c\
	main.c \
	parsing/map.c \
	parsing/parse_grid.c \
	parsing/parse_metadata.c \
	parsing/trim_grid.c \
	parsing/utils.c \
	parsing/check_grid.c \
	parsing/check_metadata.c \
	graphics/init_mlx.c \
	graphics/keymapping.c \
	graphics/hooks.c \
	graphics/draw_minimap.c \
	graphics/move_player.c \
	graphics/rotate_player.c \
	graphics/draw_screen.c \
	graphics/raycasting.c \
	graphics/wall_textures.c \
	graphics//wall_render.c \
	utils/mlx.c \
	utils/char.c \
	utils/error.c \
	utils/exit.c \
	utils/free.c \
	utils/string.c

SRCS = $(addprefix $(C_DIR)/,$(C_FILES))


# ************************************
# Objects                            *
# ************************************

O_DIR = $(C_DIR)/_obj

OBJS = $(addprefix $(O_DIR)/,$(C_FILES:.c=.o))


# ************************************
# Headers                            *
# ************************************

H_DIR = inc

H_FILES = cub3d.h \
	config.h

HEADERS = $(addprefix $(H_DIR)/,$(H_FILES))


# ************************************
# Flags                              *
# ************************************

CFLAGS = -Wall -Wextra -Werror


# ************************************
# Libraries                          *
# ************************************

LIBS_DIR = ../lib

LIBFT_DIR = $(LIBS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = $(LIBS_DIR)/MLX42

MLX = $(MLX_DIR)/build/libmlx42.a

LIBS = $(LIBFT) $(MLX) -ldl -lglfw -pthread -lm


# ************************************
# Includes                           *
# ************************************

INCLUDES = -I$(H_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include/MLX42


# ************************************
# Rules                              *
# ************************************

all: $(NAME)

$(O_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS) $(LIBFT) $(MLX)
	@mkdir -p $(@D)
	cc -c $(FLAGS) $< -o $@ $(INCLUDES)

$(NAME): $(OBJS) $(LIBFT)
	cc -o $@ $^ $(LIBS)

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re
