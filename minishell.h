/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/05/31 17:46:30 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef HEADER_H
#define HEADER_H

#define MAX_TOKENS 100
#define TOKEN_COMMAND 0
#define TOKEN_PIPE 1
#define I_RED 2 // <
#define O_RED 3 // >
#define H_DOC 4 // <<
#define O_APP 5 // >>

typedef struct s_prompt
{
	char			*cmd;
	char			*file;
	int				red_typ;
	struct s_prompt	*next;
}	t_prompt;

char	**ft_split(const char *s, char c);
void	check_qoutes(char *s, char qoute);
size_t  ft_strcspn(const char *s, const char *reject);

#endif