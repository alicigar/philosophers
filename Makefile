NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = clean.c init.c main.c monitor.c parsing.c time.c utils.c routine.c eat.c 
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re