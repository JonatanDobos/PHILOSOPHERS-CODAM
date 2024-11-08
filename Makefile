NAME	=	philo

CC		=	cc
CC		+=	-g
# CC		+=	-fsanitize=address

CFLAGS	=	-Wall -Wextra -Werror -pthread
CFLAGS	+=	-Wunused -Wuninitialized -Wunreachable-code
CFLAGS	+=	-flto

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/input_handling.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/monitor.c \
			$(SRCDIR)/philo_routine.c \
			$(SRCDIR)/utils_pthread.c \
			$(SRCDIR)/activities.c \
			$(SRCDIR)/malloc_and_free.c

OBJ		=	$(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
