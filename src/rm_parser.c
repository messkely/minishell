/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:10:26 by messkely          #+#    #+#             */
/*   Updated: 2024/06/28 18:21:20 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arglen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	*rm_escape_char(char *s)
{
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;
	char	*res;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			res[j++] = s[i];
		i++;
	}
	return (free(s), res[j] = '\0', res);
}

static int	count_valid_elements(char *args[], int n)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0
			|| ft_strcmp(args[i], ">>") == 0 || ft_strcmp(args[i], "<<") == 0)
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

char	**rm_red_args_cp(char *args[], t_prompt *pmp, char **new_args)
{
	int		i;
	int		j;
	int		file_index;

	j = 0;
	i = 0;
	file_index = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<")
			|| !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
		{
			pmp->file[file_index++] = ft_strdup(args[i]);
			if (args[i + 1])
				pmp->file[file_index++] = ft_strdup(args[++i]);
		}
		else
			new_args[j++] = ft_strdup(args[i]);
		i++;
	}
	ft_broom(args);
	return (new_args[j] = NULL, pmp->file[file_index] = NULL, new_args);
}

char	**rm_red_args(char *args[], int n, t_prompt *pmp)
{
	char	**new_args;
	int		new_size;

	new_size = count_valid_elements(args, n);
	new_args = malloc((new_size + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	pmp->file = malloc((n - new_size + 1) * sizeof(char *));
	if (!pmp->file)
		return (ft_broom(new_args), NULL);
	return (rm_red_args_cp(args, pmp, new_args));
}
