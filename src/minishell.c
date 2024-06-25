/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/06/25 22:28:35 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_prompt *pmp)
{
	char	**arr;
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		input = ft_strtrim(input, " ");
		if (check_syntax(input))
		{
			free(input);
			continue ;
		}
		arr = process_token(input, '|');
		fill_stack(arr, pmp);
        for (int i = 0; arr[i]; i++)
            free(arr[i]);
        free(arr);
        free(input);
	}
}
void f(void)
{
	system("leaks ./minishell");
}
int	main(int ac, char **av, char **env)
{
	t_prompt	*prompt = NULL;

	atexit(f);
	(void)ac;
	(void)av;
	(void)env;
	ft_parser(prompt);
	return (0);
}

// cat file1 > file2 file3 >> file4 file5 file6 | cat file1 > file2 file3 >> file4 file5 file6
