NAME = cub3D

# Compiler

CC = gcc

# Flags

CFLAGS = -Wall -Wextra -Werror -I mlx

# Sources

SRC = parsing.c get_next_line_utils.c cub3d.c

# Objects

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all