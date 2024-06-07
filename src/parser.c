/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:54:43 by messkely          #+#    #+#             */
/*   Updated: 2024/06/07 10:49:45 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_red(int c1, int c2)
{
	if ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>')
		|| (c1 == '>' || c1 == '<'))
		return (1);
	else if ((c1 == '<' && c2 == '>')
		|| (c1 == '>' && c2 == '<'))
		return (-1);
	else
		return (0);
}

char *get_last_arg(const char *s, int del)
{
	if (!s)
		return (0);
	while(*s)
	{
		if (del)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	check_multi_pipe(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;
	int pip_count;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	pip_count = 0;
	if (s[i] == '|')
		ft_error("minishell: syntax error near unexpected token `|'");
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (s[i] == '|'  && s[i + 1] == '|' && !double_quote && !single_quote)
			ft_error("minishell: syntax error near unexpected token `|'");
		if (s[i] == '|' && !double_quote && !single_quote)
			pip_count++;
		i++;
	}
}

char	*substr(const char *str, int start, int end)
{
	int i;
	int substr_len;
	char *substr;

	i = 0;
	substr_len = end - start;
	substr = malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (str[start] && start < end)
		substr[i++] = str[start++];
	substr[substr_len] = '\0';
	return (substr);
}

char	**process_token(char *s)
{
	int		i;
	int		start;
	int		double_quote;
	int		single_quote;
	int		backslash;
	int		tok_count;
	char	**av;

	i = 0;
	start = 0;
	double_quote = 0;
	single_quote = 0;
	backslash = 0;
	tok_count = 0;
	check_quotes(s);
	check_multi_pipe(s);
	av = malloc(100 * sizeof(char *));
	if (!av)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\\' && !backslash && !single_quote)
			backslash = 1;
		else if (s[i] == '\\' && backslash)
			backslash = 0;
		else if (s[i] != '\\' && backslash)
			backslash = 0;
		else if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		if (s[i] == '|' && !single_quote && !double_quote && !backslash)
		{
			av[tok_count++] = substr(s, start, i);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
		av[tok_count++] = substr(s, start, i);
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
				return (av = strdup(get_last_arg((char *)&s[i], 1)), av);
			else
				ft_error("redirection Error1");
		}
		else if (check_red(s[i], s[i + 1]) < 0)
			ft_error("redirection Error2");
		i++;
	}
	return (av);
}

void	ft_error(char *s)
{
	printf("minishell: %s\n", s);
	exit(1);
}