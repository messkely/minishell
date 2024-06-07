#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_error(char *s)
{
	printf("minishell: %s\n", s);
	exit(1);
}

void	check_quotes(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;
	int	backslash;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (s[i])
	{
		if (s[i] == '\\' && !backslash && !single_quote)
			backslash = 1;
		else if (s[i] == '\\' && backslash)
			backslash = 0;
		else if (s[i] != '\\' && backslash)
			backslash = 0;
		else if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote || backslash)
		printf("syntax error: unclosed quotes or backslashes\n");
}

char	is_escape(char c, int *single_quote, int *double_quote, int *backslash)
{
	if (c == '\\' && !(*backslash) && !(*single_quote))
		return (*backslash = 1, 0);
	else if (c == '\\' && *backslash)
		return (*backslash = 0, c);
	else if (c != '\\' && *backslash)
		return (*backslash = 0, c);
	else if (c == '\'' && !(*double_quote))
		return (*single_quote = !(*single_quote), 0);
	else if (c == '"' && !(*single_quote))
		return (*double_quote = !(*double_quote), 0);
	else
		return (c);
}


char	*rm_escape_char(char *s)
{
	int		i;
	int		j;
	char	*res;
	int		single_quote;
	int		double_quote;
	int		backslash;
	char	escaped;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	backslash = 0;
	check_quotes(s);
	res = malloc(strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[i])
	{
		escaped = is_escape(s[i], &single_quote, &double_quote, &backslash);
		if (escaped)
			res[j++] = escaped;
		i++;
	}
	return (res[j] = '\0', res);
}

int main()
{
	while (1)
	{
		char *s = readline("test> ");
		if (s == NULL)
			break;
		char *new_str = rm_escape_char(s);
		printf("%s\n", new_str);
		free(new_str);
		free(s);
	}
	return 0;
}