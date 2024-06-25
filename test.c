#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void ft_error(const char *msg, char c)
{
	fprintf(stderr, msg, c);
}

int check_red_pattern(char *s, int *i)
{
	int j = *i;

	if (s[j] == '<' && s[j + 1] == '<')
		j += 2;
	else if (s[j] == '>' && s[j + 1] == '>')
		j += 2;
	else if (s[j] == '<' && s[j + 1] == '>')
		j += 2;
	else if (s[j] == '<' || s[j] == '>')
		j++;
	else
		return (0);
	while (s[j] && s[j] == ' ')
		j++;
	if (!s[j] || (s[j] == '<' || s[j] == '>'))
		return (0);
	*i = j - 1;
	return (1);
}

int check_syntax_red(char *s)
{
	int single_quote = 0;
	int double_quote = 0;
	int i = 0;

	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if ((s[i] == '<' || s[i] == '>') && !single_quote && !double_quote)
		{
			if (!check_red_pattern(s, &i))
			{
				ft_error("syntax error near unexpected token `%c'\n", s[i]);
				return (1);
			}
		}
		i++;
	}

	return 0;
}

int check_syntax(char *input)
{
	if (check_syntax_red(input))
		return (1);
	return (0);
}

int main()
{
	char *input;

	while (1)
	{
		input = readline("input> ");
		if (check_syntax(input))
			printf("Syntax error detected\n");
		free(input);
	}

	return (0);
}
