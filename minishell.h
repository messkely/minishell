/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/06/25 11:15:05 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libftt/libft.h"
# define MAX_TOKENS 100

typedef struct s_prompt
{
	char			**argv;
	char			**file;
	struct s_prompt	*next;
}	t_prompt;

int			check_syntax(char *input);
char		*rm_escape_char(char *s);
char		**process_token(char *s, char token);

t_prompt	*ft_lstnew(char *content);
void		ft_add_back(t_prompt *head, t_prompt *new);
void		ft_error(char *s, char c);
void		fill_stack(char **arr, t_prompt *pmp);

char **rm_red_args(char *args[], int n, t_prompt *pmp);
int ft_arglen(char **args);

#endif