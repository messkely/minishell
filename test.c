#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to process tokens while handling quotes and skipping multiple consecutive tokens
char **process_token(char *s, char token)
{
    int i = 0;
    int start = 0;
    int double_quote = 0;
    int single_quote = 0;
    int tok_count = 0;
    char **av;

    av = malloc((strlen(s) / 2 + 2) * sizeof(char *));
    if (!av)
        return NULL;
    while (s[i])
	{
        if (s[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (s[i] == '"' && !single_quote)
            double_quote = !double_quote;
        if (s[i] == token && !single_quote && !double_quote)
		{
            if (i > start)
                av[tok_count++] = strndup(s + start, i - start);
            while (s[i] == token)
                i++;
            start = i;
        }
		else
            i++;
    }
    if (start < i)
        av[tok_count++] = strndup(s + start, i - start);
    return (av[tok_count] = NULL, av);
}

int main() {
    char input[] = "echo \"Hello, world\" > file 'and this' > other";
    char **tokens = process_token(input, '>');
    
    if (tokens) {
        for (int i = 0; tokens[i]; i++) {
            printf("Token %d: %s\n", i, tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
}

