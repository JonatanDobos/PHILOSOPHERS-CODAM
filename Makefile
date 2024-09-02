NAME	=	philo

CC		=	cc -g -fsanitize=address

# CFLAGS=		-Wall -Wextra -Werror

# SRCDIR	=	./test_env_src
# SRC	=	$(SRCDIR)/main.c

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/utils.c
			$(SRCDIR)/init.c

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
