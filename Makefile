NAME 	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lreadline
SRC		= src/main.c src/ft_split.c src/tokens_fun.c src/parser.c
OBJ 	= $(SRC:.c=.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all clean
	clear

.PHONY: clean