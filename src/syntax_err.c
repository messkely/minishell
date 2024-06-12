/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:15:54 by messkely          #+#    #+#             */
/*   Updated: 2024/06/12 10:53:36 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ispace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_error(char *s, char c)
{
	if (c == '\n')
		printf("minishell: %s newline\n", s);
	else
		printf("minishell: %s `%c'\n", s, c);
}

static int	check_multi_pipe(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (s[i] == '|')
		return (ft_error("syntax error near unexpected token `|'", 0), 1);
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (s[i] == '|' && !double_quote && !single_quote)
		{
			while (s[i] && ft_ispace(s[i]))
				i++;
			if (s[i] == '|')
				return (ft_error("syntax error near unexpected token `|'", 0), 1);
		}
		i++;
	}
	return (0);
}

int	red_cases(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>')
		|| ((c1 == '<' || c1 == '>') && (c2 != '<' && c2 != '>'))
		|| (c1 == '<' && c2 == '>'));
}

int	check_red(char *s, int *i)
{
	int	red;

	red = 0;
	while (s[*i])
	{
		while (s[*i] && s[*i] == ' ')
			(*i)++;
		if (s[*i] == '\0')
			return (0);
		if (red_cases(s[*i], s[*i + 1]) && !red)
		{
			red = 1;
			(*i)++;
			if (red_cases(s[*i + 1], s[*i + 1]))
				return (0);
			(*i)++;
			continue ;
		}
		else if ((s[*i] != '<' && s[*i] != '>'))
			return (1);
		else
			return (0);
		(*i)++;
	}
	return (0);
}

int	check_syntax_red(char *s)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if ((s[i] == '>' || s[i] == '<') && !double_quote && !single_quote)
		{
			if (!check_red((char *)&s[i], &i))
				return (ft_error("syntax error near unexpected token", s[i]), 1);
			i--;
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *input)
{
	if (check_multi_pipe(input) || check_syntax_red(input))
		return (1);
	return (0);
}

// bash-3.2$ cat > jdjd jdjd  < shiva < shiva << shiva
// hack danger :  cat >> jdjd >> jdjd >> jdjd < shiva >> jdjd << shiva ">>" jdjd