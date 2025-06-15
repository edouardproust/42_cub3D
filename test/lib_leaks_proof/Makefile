NAME	:= test
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ../../lib/MLX42

HEADERS	:= -I $(LIBMLX)/include/MLX42
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)
	valgrind ./$(NAME) #-s --leak-check=full --show-leak-kinds=all ./$(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
