NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	=  -lmlx -framework OpenGL -framework AppKit
FT_PRINTF_DIR = printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

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
	utils/utils.c \
	utils/parse.c \
	utils/parse_utils.c \

HEADER = includes/so_long.h

OBJ			= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(FT_PRINTF_LIB) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re