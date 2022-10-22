NAME = cub3D

# Compiler

CC = gcc

# Flags

CFLAGS = -Wall -Wextra -Werror -I mlx #-fsanitize=address -g

# Sources

SRC = parsing/data_parsing/data_parser.c \
	parsing/map_parsing/map_parsing.c \
	parsing/map_parsing/map_checker.c \
	parsing/texture_parsing/texture_parsing.c \
	parsing/texture_parsing/texture_checker.c \
	parsing/parsing.c \
	utils/2d_arr_utils.c \
	utils/str_utils.c \
	utils/str_utils2.c \
	utils/str_utils3.c \
	cub3d.c \
	draw.c \
	img_utils.c \

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