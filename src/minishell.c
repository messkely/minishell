/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/06/24 08:52:30 by messkely         ###   ########.fr       */
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
		// if (check_syntax(input))
		// {
		// 	free(input);
		// 	continue ;
		// }
		arr = process_token(input, '|');
		if (!arr)
		{
			free(input);
			continue ;
		}
		fill_stack(arr, pmp);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_prompt	*prompt = NULL;

	(void)ac;
	(void)av;
	(void)env;
	ft_parser(prompt);
	return (0);
}
