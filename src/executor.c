#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	static int status;
	char **tokens;
	while (1)
	{
		char *path = "/bin/";
		char *input = readline("minishell> ");
		if (input == NULL)
			break ;
		input[strcspn(input, "\n")] = '\0';
		tokens = ft_split(input, ' ');
		path = ft_strjoin(path, tokens[0]);
		pid_t pid = fork();
		if (pid == 0)
		{
			execve(path, tokens, env);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
		free(input);
		free(tokens);
	}

	return 0;
}