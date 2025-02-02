NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_DIR		= libs/minilibx_opengl_20191021
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRC	= src/main.c \
	src/map_parser.c \
	src/render.c \
	src/hooks.c \
	src/game_logic.c \
	utils/ft_strlcpy.c \
	utils/ft_strlen.c \
	utils/get_next_line.c \
	utils/get_next_line_utils.c \
	utils/ft_strcmp.c \

HEADER = includes/so_long.h

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 