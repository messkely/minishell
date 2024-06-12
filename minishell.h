/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/06/12 10:34:42 by messkely         ###   ########.fr       */
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
# include "./libft/libft.h"
# define MAX_TOKENS 100

typedef struct s_prompt
{
	char			**argv;
	char			*file;
	struct s_prompt	*next;
}	t_prompt;

int			check_syntax(char *input);
char		*rm_escape_char(char *s);
char		**process_token(char *s, char token);
char		*process_red(char *s);

t_prompt	*ft_lstnew(char *content);
void		ft_add_back(t_prompt *head, t_prompt *new);
void		ft_error(char *s, char c);
void		fill_stack(char **arr, t_prompt *pmp);

#endif