/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:28:39 by messkely          #+#    #+#             */
/*   Updated: 2024/06/25 11:16:06 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_prompt *ft_lstnew(char *data)
{
    t_prompt *new;
    int i;

    new = malloc(sizeof(t_prompt));
    if (!new)
        return (NULL);
    new->file = malloc(100 * sizeof(char *));
    if (!new->file)
    {
        free(new);
        return (NULL);
    }
    data = ft_strtrim(data, " ");
    new->argv = process_token(data, ' ');
	free(data);
    if (!new->argv)
    {
        free(new);
        return (NULL);
    }
    i = 0;
    while (new->argv[i])
    {
        new->argv[i] = rm_escape_char(new->argv[i]);
        i++;
    }
    new->argv = rm_red_args(new->argv, ft_arglen(new->argv), new);

    for (int i = 0; new->argv[i]; i++)
        printf("argv[%d] %s\n",i, new->argv[i]);

    for (int i = 0; new->file[i] != NULL; i++)
        printf("file [%d] %s\n",i, new->file[i]);
    printf("########################\n");

    new->next = NULL;
    return new;
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

