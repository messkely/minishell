/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:15:54 by messkely          #+#    #+#             */
/*   Updated: 2024/05/31 17:53:26 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	check_qoutes(char *s, char qoute)
{
	int i = 0;
	int flg = 1;

	while (s[i])
	{
		if (s[i] == qoute)
		{
			flg = 0;
			i++;
			while (s[i] && s[i] != qoute)
				i++;
		}
		if (s[i] == qoute)
			flg = 1;
		i++;
	}
	if (s[i] == '\0' && !flg)
	{
		printf("error");
		exit(1);
	}
	else
	{
		printf("all qoutes is closed");
		exit(0);
	}
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

t_prompt	*ft_lstnew(void *content)
{
	t_prompt	*new;
	char		**tmp;

	new = malloc(sizeof(t_prompt));
	if (new != NULL)
	{
		new->cmd = content;
		new->file = NULL;
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

void	ft_add_back(t_prompt **head, t_prompt *new)
{
	t_prompt	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = ft_last_node(*head);
	last->next = new;
}