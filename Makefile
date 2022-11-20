NAME = philo

SRCS =  philo.c\
		init.c\
		routine.c\
		time.c\
		utils.c

OBJS =	$(SRCS:.c=.o)

RM = rm -f

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:	$(NAME)

clean:
		$(RM)	$(OBJS)

fclean:		clean
			$(RM)	$(NAME)

re:		fclean	all

.PHONY: all clean fclean re
