/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:39 by messkely          #+#    #+#             */
/*   Updated: 2024/06/29 11:29:30 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_broom(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_prompt	*ft_lstnew(char *data)
{
	t_prompt	*new;
	int			i;

	new = malloc(sizeof(t_prompt));
	if (!new)
		return (NULL);
	data = ft_strtrim(data, " ");
	data = add_space_in_red(data);
	new->argv = process_token(data, ' ');
	free(data);
	if (!new->argv)
		return (free(new), NULL);
	i = 0;
	while (new->argv[i])
	{
		new->argv[i] = rm_escape_char(new->argv[i]);
		i++;
	}
	new->argv = rm_red_args(new->argv, ft_arglen(new->argv), new);
	i = 0;
	while (new->argv[i])
	{
		printf("argv[%d] %s\n", i, new->argv[i]);
		i++;
	}
	i = 0;
	while (new->file[i] != NULL)
	{
		printf("file [%d] %s\n", i, new->file[i]);
		i++;
	}
	printf("########################\n");
	ft_broom(new->argv);
	if (new->file)
		ft_broom(new->file);
	else
		free(new->file);
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

void	fill_stack(char **arr, t_prompt *pmp)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_add_back(pmp, ft_lstnew(arr[i++]));
}
