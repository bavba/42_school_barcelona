NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c parse_arguments.c execute_instructions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

