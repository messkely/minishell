#include "minishell.h"

int ft_echo(char **av)
{
	int i;
	int is_option;

	i = 1;
	is_option = 0;
	while (av[i] != NULL && (ft_strcmp(av[i], "-n") == 0
		|| ft_strcmp(av[i], "-e") == 0))
	{
		if (ft_strcmp(av[i], "-n") == 0)
			is_option = 1;
		i++;
	}
	// printf("is_option: %s\n", av[i - 1]);
	while (av[i] != NULL)
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (is_option == 0)
		write(1, "\n", 1);
	return (0);
}

int main()
{
	// char *line[] = 	{"echo", "-e", "-e", "-n", "-e", "hello", "world", NULL};
	char *line[] = 	{"echo", "-e", "hello", "world", NULL};
	return (ft_echo(line));
}
// echo ->n djd sls
