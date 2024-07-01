/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/07/01 06:46:35 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_prompt_list(t_prompt *head)
{
    t_prompt *current = head;
    int i;

    while (current)
    {
        printf("Node:\n");
        i = 0;
        while (current->argv && current->argv[i])
        {
            printf("argv[%d]: %s\n", i, current->argv[i]);
            i++;
        }
        
        i = 0;
        while (current->file && current->file[i])
        {
            printf("file[%d]: %s\n", i, current->file[i]);
            i++;
        }
        
        printf("########################\n");
        current = current->next;
    }
}


void ft_parser(t_prompt *pmp)
{
	char **arr;
	char *input;
	int i;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break;
		char *trimmed_input = ft_strtrim(input, " ");
		free(input);
		if (check_syntax(trimmed_input))
		{
			free(trimmed_input);
			continue;
		}
		arr = process_token(trimmed_input, '|');
		if (!arr)
			continue;
		i = 0;
		while (arr[i])
			ft_add_back(&pmp, ft_lstnew(arr[i++]));
		ft_broom(arr);
		print_prompt_list(pmp);
		free_list(pmp);
		return ;
	}
}

void f()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
    t_prompt *prompt = NULL;

    atexit(f);
    (void)ac;
    (void)av;
    (void)env;
    ft_parser(prompt);
    return (0);
}

//  cat > file1 | echo > file2
