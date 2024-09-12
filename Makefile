NAME	=	philo

CC		=	cc

# CC		=	cc -g -fsanitize=address

# CFLAGS=		-Wall -Wextra -Werror

# SRCDIR	=	./test_env_src
# SRC	=	$(SRCDIR)/main.c

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/observer.c \
			$(SRCDIR)/mutex.c \
			$(SRCDIR)/activities.c \
			$(SRCDIR)/malloc_and_free.c

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
