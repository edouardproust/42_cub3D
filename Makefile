NAME = ./cub3D

NAME_BONUS = ./cub3D_bonus


# ************************************
# Dirs                               *
# ************************************

MANDATORY_DIR = mandatory

BONUS_DIR = bonus


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
	@if [ -f "$(MLX_DIR)/build/CMakeCache.txt" ]; then \
		if [ "$$(stat -c %Y Makefile)" -gt "$$(stat -c %Y $(MLX_DIR)/build/CMakeCache.txt)" ]; then \
			rm -rf $(MLX_DIR)/build; \
		fi; \
	fi
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


# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft libmlx
