/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:39 by messkely          #+#    #+#             */
/*   Updated: 2024/06/12 10:41:28 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_prompt	*ft_lstnew(char *data)
{
	t_prompt *new;
	int i;
	int j;

	i = 0;
	new = malloc(sizeof(t_prompt));
	if (!new)
		return (NULL);
	new->argv = process_token(ft_strtrim(data, " "), ' ');
	if (!new->argv)
	{
		free(new);
		return (NULL);
	}
	while (new->argv[i])
	{
		new->argv[i] = rm_escape_char(new->argv[i]);
		i++;
	}
	new->file = process_red(data);
	i = 0;
	j = 0;
	while (new->argv[i])
	{
		printf("argv[%d] = %s\n", j++, new->argv[i++]);
	}
	printf("file = %s\n", new->file);
	printf("########################\n");
	return (new->next = NULL, new);
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

