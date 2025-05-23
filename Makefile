NAME = ./cub3D

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

O_DIR = src/_obj

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

LIBS_DIR = lib

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

all: libft libmlx $(NAME)

$(O_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	cc -c -o $@ $< $(INCLUDES) $(CFLAGS)

$(NAME): $(OBJS) $(LIBFT)
	cc -o $@ $^ $(LIBS)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(O_DIR)
	rm -rf $(MLX)/build

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(MLX)

re: fclean all

libft:
	$(MAKE) -C $(LIBFT_DIR)

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	$(MAKE) -C $(MLX_DIR)/build -j4

VALGRIND_SUPP = valgrind.supp

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=$(VALGRIND_SUPP) $(NAME) assets/maps/_valgrind_test.cub


# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft libmlx valgrind
