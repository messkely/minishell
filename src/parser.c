/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:54:43 by messkely          #+#    #+#             */
/*   Updated: 2024/06/25 11:17:39 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	
	av = malloc((strlen(s) / 2 + 2) * sizeof(char *));
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
			av[tok_count++] = strndup(s + start, i - start);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
		av[tok_count++] = strndup(s + start, i - start);

	av[tok_count] = NULL;
	return av;
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
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 ||
            strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0)
            i++;
        else
            count++;
        i++;
    }
    return count;
}

char **rm_red_args(char *args[], int n, t_prompt *pmp)
{
    int new_size = count_valid_elements(args, n);
    char **new_args = (char **)malloc((new_size + 1) * sizeof(char *));
    int j = 0;
    int i = 0;
    int file_index = 0;

    while (i < n)
    {
        if (!strcmp(args[i], ">") || !strcmp(args[i], "<") ||
            !strcmp(args[i], ">>") || !strcmp(args[i], "<<"))
        {
            if (i + 1 < n)
            {
                pmp->file[file_index++] = strdup(args[i]);
                pmp->file[file_index++] = strdup(args[++i]);
            }
        }
        else
        {
            new_args[j++] = strdup(args[i]);
        }
        i++;
    }
    new_args[j] = NULL;
    pmp->file[file_index] = NULL;
    for (int k = 0; k < n; k++)
        free(args[k]);
    free(args);

    return new_args;
}
