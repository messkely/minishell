/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:20:08 by messkely          #+#    #+#             */
/*   Updated: 2024/06/10 20:21:59 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	static int	status;
	char		**tokens;
	char		*path;
	char		*input;
	pid_t		pid;

	(void)ac;
	(void)av;
	while (1)
	{
		path = "";
		input = readline("executor> ");
		if (input == NULL)
			break ;
		input[strcspn(input, "\n")] = '\0';
		tokens = ft_split(input, ' ');
		path = ft_strjoin(path, tokens[0]);
		pid = fork();
		if (pid == 0)
		{
			execve(path, tokens, env);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
		free(input);
		free(tokens);
	}
	return (0);
}
