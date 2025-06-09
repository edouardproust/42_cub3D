NAME = ./cub3D

NAME_BONUS = ./cub3D_bonus


# ************************************
# Dirs                               *
# ************************************

MANDATORY_DIR = mandatory

BONUS_DIR = bonus

# ************************************
# OPTIONS                            *
# ************************************

VALGRIND_SUPP = valgrind.supp

VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=$(VALGRIND_SUPP)

VALGRIND_MAP = $(MANDATORY_DIR)/assets/maps/test.cub

VALGRIND_MAP_BONUS = $(BONUS_DIR)/assets/maps/test.cub


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
# Rules                              *
# ************************************

all: libft libmlx
	$(MAKE) -C $(MANDATORY_DIR)

bonus: libft libmlx
	$(MAKE) -C $(BONUS_DIR)

libft:
	$(MAKE) -C $(LIBFT_DIR)

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	$(MAKE) -C $(MLX_DIR)/build -j4

clean:
	$(MAKE) -C $(MANDATORY_DIR) clean
	$(MAKE) -C $(BONUS_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX)/build

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

valgrind:
	valgrind $(VALGRIND_MAP) $(VALGRIND_FLAGS)

valgrind_bonus:
	valgrind $(VALGRIND_MAP_BONUS) $(VALGRIND_FLAGS)


# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft libmlx valgrind
