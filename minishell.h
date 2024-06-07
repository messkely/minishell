/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/06/07 11:02:27 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MINISHELL_H
#define MINISHELL_H

#define MAX_TOKENS 100

typedef struct s_prompt
{
	char			**argv;
	char			*file;
	int				red_typ;
	struct s_prompt	*next;
}	t_prompt;

void		check_quotes(char *s);
char		*rm_escape_char(char *s);
char		**process_token(char *s);
char		*process_red(char *s);
char		is_escape(char c, int *single_quote, int *double_quote, int *backslash);

size_t  	ft_strcspn(const char *s, const char *reject);
t_prompt	*ft_lstnew(char *content);
void		ft_add_back(t_prompt *head, t_prompt *new);
void    	ft_error(char *s);
size_t  	ft_strlen(const char *s);
char		**ft_split(const char *s, char c);
void		fill_stack(char **arr, t_prompt *pmp);

#endif