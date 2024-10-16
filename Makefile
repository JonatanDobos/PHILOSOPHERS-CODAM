NAME	=	philo

CC		=	cc

# CC		=	cc -g -fsanitize=address

CFLAGS=		-Wall -Wextra -Werror

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/utils_print.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/observer.c \
			$(SRCDIR)/utils_pthread.c \
			$(SRCDIR)/activities.c \
			$(SRCDIR)/malloc_and_free.c

OBJ	=	$(SRC:.c=.o)

ifeq ($(filter no_rules,$(MAKECMDGOALS)),no_rules)
	CFLAGS += -D EXPLICIT_RULES=false
endif

# ifeq ($(filter color,$(MAKECMDGOALS)),debug)
# 	CFLAGS += -D DEBUG=true
# endif

all: $(NAME) 

no_rules: all

debug: all

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
