/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/05/29 19:52:28 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenize(char *input)
{
	t_token *tokenList;
	char **tmp;
	int i;

    tokenList = malloc(sizeof(t_token));
    if (!tokenList)
	{
        write(1, "Allocation error\n", 17);
        exit(1);
    }

    tokenList->count = 0;
    tmp = ft_split(input, ' ');
	i = 0;
    while (tmp[i] != NULL)
	{
        if (tokenList->count >= MAX_TOKENS)
		{
            write(1, "Too many tokens\n", 16);
            exit(1);
        }
        tokenList->tokens[tokenList->count++] = tmp[i++];
    }

    tokenList->tokens[tokenList->count] = NULL;
    return (tokenList);
}

int main() {
    char input[1024];
    t_token *tokenList;

	while (1)
	{
		char *input = readline("minishell> ");
		if (input == NULL)
			break;
        input[strcspn(input, "\n")] = '\0';

        tokenList = tokenize(input);
        if (tokenList->count == 0) {
            free(tokenList);
            continue;
        }


        for (int i = 0; i < tokenList->count; i++) {
            printf("Token[%d]: %s\n", i, tokenList->tokens[i]);
        }

        free(tokenList);
		free(input);
		wait(NULL);
	}
    return 0;
}
