/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/05/31 17:50:45 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_stack(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_add_back(lst, ft_add_new_node(ft_atoi(arr[i++])));
	ft_broom(arr);
}

void	ft_parser(t_prompt *prompt)
{
	char **arr;
	int i = 0;
	
	while (1)
	{
		char *input = readline("minishell> ");
		if (input == NULL)
			break ;
        input[ft_strcspn(input, "\n")] = '\0';
        arr = ft_split(input, '|');
        fill_stack(arr);
		// what i want to do when i splite cmd
		while (arr[i])
			printf("%s \n", arr[i++]);

		free(input);
		wait(NULL);
	}
}

int main(int ac, char **av, char **env)
{
	t_prompt prompt;

	(void)ac;
	(void)av;
	int i = 0;
    ft_parser(&prompt);
	while (env[i])
		printf("%s\n", env[i++]);
	
    return 0;
}