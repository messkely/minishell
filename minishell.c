/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:16:09 by yiken             #+#    #+#             */
/*   Updated: 2024/07/12 16:11:03 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_beta_pid = -1;
char	*expd_line(char **envp, char *str, int status);
char	*ft_strdup(char *str);
void	ft_parser(t_smplcmd **pmp, char *input);
int		exec_cmds(t_smplcmd *cmdlst, char ***envp);

void	clean_envpd(char **envpd, int i)
{
	while (i >= 0)
		free(envpd[i--]);
	free(envpd);
}

char	**envp_dup(char **envp)
{
	char	**envpd;
	int		i;
	int		cntr;

	cntr = 0;
	while (envp[cntr])
		cntr++;
	envpd = malloc(sizeof(char *) * (cntr + 1));
	if (!envpd)
		return (perror("malloc"), NULL);
	i = 0;
	while (envp[i])
	{
		envpd[i] = ft_strdup(envp[i]);
		if (!envpd[i])
			break ;
		i++;
	}
	envpd[i] = 0;
	if (cntr != i)
		return (clean_envpd(envpd, i), NULL);
	return (envpd);
}

int	minishell_loop(t_smplcmd **cmdlst, char	***envp)
{
	char		*line;
	char		*expdd_line;
	int			status;

	status = 0;
	while (1)
	{
		rl_catch_signals = 0;
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		line = ft_strtrim(line, " ");
		if (!(*line) || check_syntax(line))
		{
			if (!(*line))
				c_handle_signals();
				// exit_status(2);
			continue ;
		}
		expdd_line = expd_line(*envp, line, status);
		if (!expdd_line)
			continue ;
		free(line);
		ft_parser(cmdlst, expdd_line);
		status = exec_cmds(*cmdlst, envp);
		free_list(cmdlst);
	}
	return (status);
}

static void	free_nenvp(char **nenvp)
{
	int	i;

	i = 0;
	while (nenvp[i])
		free(nenvp[i++]);
	free(nenvp);
}

int	main(int ac, char **av, char **envp)
{
	char		**nenvp;
	t_smplcmd	*cmdlst;
	int			status;

	(void)av;
	cmdlst = NULL;
	if (ac != 1)
		return (write(2, "Wrong arguments number\n", 23));
	nenvp = envp_dup(envp);
	if (!nenvp)
		return (write(2, "envp duplication error\n", 23), 1);
	ft_handle_signals();
	status = minishell_loop(&cmdlst, &nenvp);
	free_nenvp(nenvp);
	return (status);
}
