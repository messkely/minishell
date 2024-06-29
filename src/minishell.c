/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/06/29 12:52:16 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_list(t_prompt *head)
{
	t_prompt *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->argv)
			ft_broom(tmp->argv);
		if (tmp->file)
			ft_broom(tmp->file);
		free(tmp);
	}
}

void	ft_parser(t_prompt *pmp)
{
	char	**arr;
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n\n\n\n");
			break;
		}
		input = ft_strtrim(input, " ");
		if (check_syntax(input))
		{
			free(input);
			continue ;
		}
		arr = process_token(input, '|');
		free(input);
		fill_stack(arr, pmp);
		free_list(pmp);
		break ;
	}
}
void f()
{
	system("leaks minishell");
}
int	main(int ac, char **av, char **env)
{
	t_prompt	*prompt;

	prompt = NULL;
	(void)ac;
	(void)av;
	(void)env;
	atexit(f);
	ft_parser(prompt);
	free_list(prompt);
	free(prompt);
	printf("exit\n\n\n\n");
	return (0);
}

//  cat < dhd djsk | echo hello
