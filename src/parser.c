/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:54:43 by messkely          #+#    #+#             */
/*   Updated: 2024/06/27 15:51:52 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *add_space_in_red(const char *s)
{
	int i;
	int	j;
	int double_quote = 0, single_quote = 0;
    char *new_s;

	i = 0;
	j = 0;
	new_s = malloc(ft_strlen(s) * 2 + 1);
    if (!new_s)
        return (NULL);
    while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (s[i] == '"' && !single_quote)
            double_quote = !double_quote;
        if ((s[i] == '<' || s[i] == '>') && !single_quote && !double_quote)
		{
            if (i > 0 && !ft_isspace(s[i - 1]))
                new_s[j++] = ' ';
            new_s[j++] = s[i];
            if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
                new_s[j++] = s[i++];
            if (s[i + 1] && !ft_isspace(s[i + 1]))
                new_s[j++] = ' ';
        }
		else
            new_s[j++] = s[i];
		i++;
    }
    new_s[j] = '\0';
    return new_s;
}

char **process_token(char *s, char token)
{
    int i = 0, start = 0;
    int double_quote = 0, single_quote = 0;
    int tok_count = 0;
    char **av;

    av = malloc((strlen(s) / 2 + 2) * sizeof(char *));
    if (!av)
        return NULL;
    while (s[i])
	{
        if (s[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (s[i] == '"' && !single_quote)
            double_quote = !double_quote;
        if (s[i] == token && !single_quote && !double_quote)
		{
            if (i > start)
                av[tok_count++] = strndup(s + start, i - start);
            while (s[i] == token)
                i++;
            start = i;
        }
		else
            i++;
    }
    if (start < i)
        av[tok_count++] = strndup(s + start, i - start);
    return (av[tok_count] = NULL, av);
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

int ft_arglen(char **args)
{
    int i = 0;
    while (args[i])
        i++;
    return (i);
}

static int count_valid_elements(char *args[], int n)
{
    int count = 0;
    int i = 0;
    while (i < n)
    {
        if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0 ||
            ft_strcmp(args[i], ">>") == 0 || ft_strcmp(args[i], "<<") == 0)
            i++;
        else
            count++;
        i++;
    }
    return count;
}

char **rm_red_args(char *args[], int n, t_prompt *pmp)
{
	char	**new_args;
    int 	new_size;
	int		i;
	int		j;
	int		file_index;

    j = 0;
    i = 0;
    file_index = 0;
	new_size = count_valid_elements(args, n);
    new_args = malloc((new_size + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	pmp->file = malloc((n - new_size + 1) * sizeof(char *));
	 if (!pmp->file)
        return (ft_broom(new_args), NULL);
    while (i < n)
    {
        if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<") ||
            !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
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
// >> |
// syntax error near unexpected token `>'