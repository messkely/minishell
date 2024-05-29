/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/05/29 19:51:13 by messkely         ###   ########.fr       */
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
#define TOKEN_DELIMITERS " \t\r\n\a"

typedef struct s_token{
    char *tokens[MAX_TOKENS];
    int count;
} t_token;

t_token *tokenize(char *input);
char	**ft_split(const char *s, char c);

#endif