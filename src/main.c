/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/06/07 10:57:26 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(t_prompt *pmp)
{
	char **arr;
	
	while (1)
	{
		char *input = readline("minishell> ");
		if (input == NULL)
			break ;
        input[ft_strcspn(input, "\n")] = '\0';
        arr = process_token(input);
        fill_stack(arr, pmp);
		free(input);
		wait(NULL);
	}
}

int main(int ac, char **av, char **env)
{
	t_prompt prompt;

	(void)ac;
	(void)av;
	(void)env;
    ft_parser(&prompt);
    return 0;
}