/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:54:43 by messkely          #+#    #+#             */
/*   Updated: 2024/06/10 20:36:59 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_red(int c1, int c2)
{
	if ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>')
		|| (c1 == '>' || c1 == '<'))
		return (1);
	else if (c1 == '>' && c2 == '<')
		return (-1);
	else
		return (0);
}

char	**process_token(char *s, char token)
{
	int		i;
	int		start;
	int		double_quote;
	int		single_quote;
	int		tok_count;
	char	**av;

	i = 0;
	start = 0;
	double_quote = 0;
	single_quote = 0;
	tok_count = 0;
	av = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!av)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (s[i] == token && !single_quote && !double_quote)
		{
			av[tok_count++] = ft_substr(s, start, i);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
		av[tok_count++] = ft_substr(s, start, i);
	return (av[tok_count] = NULL, av);
}

char	*process_red(char *s)
{
	int		i;
	int		double_quote;
	int		single_quote;
	char	*av;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	av = NULL;
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (check_red(s[i], s[i + 1]) && !single_quote && !double_quote)
		{
			if (s[i + 2] != '>' || s[i + 2] != '<')
				return (av = ft_strdup(get_last_arg((char *)&s[i], 1)), av);
		}
		i++;
	}
	return (av);
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
	return (res[j] = '\0', res);
}

void	fill_stack(char **arr, t_prompt *pmp)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_add_back(pmp, ft_lstnew(arr[i++]));
}
