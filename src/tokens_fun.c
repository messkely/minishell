/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:15:54 by messkely          #+#    #+#             */
/*   Updated: 2024/06/07 10:58:17 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

size_t  ft_strlen(const char *s)
{
	size_t i = 0;

	while (s[i])
		i++;
	return (i);
}

size_t  ft_strcspn(const char *s, const char *reject)
{
    int     i = 0;
    int     j = 0;

    while (s[i] != '\0')
    {
	j = 0;
        while (reject[j] != '\0')
        {
            if(s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}

t_prompt	*ft_lstnew(char *data)
{
	t_prompt	*new;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_prompt));
	if (new != NULL)
	{
		data = rm_escape_char(data);
		new->argv = ft_split(data, ' ');
		new->file = process_red(data);
		while (new->argv[i])
		{
			printf("argv[%d] = %s\n", j++, new->argv[i++]);
		}
		printf("file = %s\n", new->file);
		printf("########################\n");
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

t_prompt	*ft_last_node(t_prompt *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_add_back(t_prompt *head, t_prompt *new)
{
	t_prompt	*last;

	if (head == NULL)
	{
		head = new;
		return ;
	}
	last = ft_last_node(head);
	last->next = new;
}

void	check_quotes(char *s)
{
	int i;
	int single_quote;
	int double_quote;
	int backslash;

	i = 0;
	single_quote = 0;
	double_quote = 0;
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
		i++;
	}
	if (single_quote || double_quote || backslash)
		ft_error("syntax error: unclosed quotes or backslashes\n");
}

char	is_escape(char c, int *single_quote, int *double_quote, int *backslash)
{
	if (c == '\\' && !(*backslash) && !(*single_quote))
		return (*backslash = 1, 0);
	else if (c == '\\' && *backslash)
		return (*backslash = 0, c);
	else if (c != '\\' && *backslash)
		return (*backslash = 0, c);
	else if (c == '\'' && !(*double_quote))
		return (*single_quote = !(*single_quote), 0);
	else if (c == '"' && !(*single_quote))
		return (*double_quote = !(*double_quote), 0);
	else
		return (c);
}

char	*rm_escape_char(char *s)
{
	int		i;
	int		j;
	char	*res;
	int		single_quote;
	int		double_quote;
	int		backslash;
	char	escaped;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	backslash = 0;
	res = malloc(strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		escaped = is_escape(s[i], &single_quote, &double_quote, &backslash);
		if (escaped)
			res[j++] = escaped;
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
