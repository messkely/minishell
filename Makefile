NAME 	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lreadline
SRC		= src/main.c src/ft_splite.c 
OBJDIR  = obj
OBJ 	= $(SRC:src/%.c=$(OBJDIR)/%.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.c minishell.h | $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re