/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/05/30 17:08:38 by messkely         ###   ########.fr       */
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
// #define TOKEN_REDIRECTION "< > << ,">>"
#define TOKEN_COMMAND 0
#define TOKEN_PIPE 1
#define I_RED 2 <
#define O_RED 3 >
#define H_DOC 4 <<
#define O_APP 5 >>


typedef struct s_token{
    char *tokens[MAX_TOKENS];
	int type[MAX_TOKENS];
    int count;
} t_token;

typedef struct s_prompt
{
	char	*cmd;
	char	*file;
	int		red_typ1;
	int		red_typ2;
	t_prompt	*next;
}	t_prompt;

t_token *tokenize(char *input);
char	**ft_split(const char *s, char c);

#endif