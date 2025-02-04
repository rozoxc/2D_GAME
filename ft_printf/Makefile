CC = cc
FLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a
HEADER = ft_printf.h
SRCS = ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c print_address.c \
		ft_strlen.c Convert_hex.c hex.c  unsigned.c 


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
