/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/06/25 11:21:29 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_prompt(t_prompt *pmp)
{
    while (pmp)
    {
        t_prompt *temp = pmp;
        pmp = pmp->next;
        for (int i = 0; temp->argv[i]; i++)
            free(temp->argv[i]);
        free(temp->argv);
        for (int i = 0; temp->file[i]; i++)
            free(temp->file[i]);
        free(temp->file);
        free(temp);
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

int	main(int ac, char **av, char **env)
{
	t_prompt	*prompt = NULL;

	(void)ac;
	(void)av;
	(void)env;
	ft_parser(prompt);
	ft_free_prompt(prompt);
	return (0);
}
