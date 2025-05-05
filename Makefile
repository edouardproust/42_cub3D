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
	parsing/valid_grid.c \
	parsing/valid_metadata.c \
	utils/char.c \
	utils/error.c \
	utils/exit.c \
	utils/free.c \
	utils/string.c \

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

MLX_DIR = $(LIBS_DIR)/minilibx

MLX = $(MLX_DIR)/libmlx_Linux.a

LIBS = $(LIBFT) -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lbsd -lm


# ************************************
# Includes                           *
# ************************************

INCLUDES = -I$(H_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)


# ************************************
# Rules                              *
# ************************************

all: libft mlx $(NAME)

$(O_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	cc -c -o $@ $< $(INCLUDES) $(CFLAGS)

$(NAME): $(OBJS) $(LIBFT)
	cc -o $@ $^ $(LIBS)

clean:
	rm -rf $(O_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(MLX)

re: fclean all

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes $(NAME) assets/maps/_valgrind_test.cub

# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft mlx valgrind
