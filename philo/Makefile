NAME = philo

SRCS = main.c \
		init.c \
		utils.c \
		parsing.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re