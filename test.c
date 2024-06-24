#include "minishell.h"

int count_valid_elements(char *args[], int n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0)
			i++;
		else
			count++;
	}
	return count;
}

void remove_redirection_args(char *args[], int n, t_prompt *pmp)
{
	int new_size = count_valid_elements(args, n);
	char **new_args = (char **)malloc(new_size * sizeof(char *));
	int j = 0;
	int i = 0;

	exit(0);
	while ( i < n)
	{
		if (!strcmp(args[i], ">") || !strcmp(args[i], "<") || !strcmp(args[i], ">>") || !strcmp(args[i], "<<"))
			pmp->file[i] = ft_strdup(args[i]);
		else
			new_args[j++] = args[i];
		i++;
	}
	pmp->file[i] = NULL;
	for (int i = 0; i < new_size; i++)
		printf("%s ", new_args[i]);
	printf("\n");
	// for (int i = 0; i < new_size; i++)
		// printf("file: %s\n", pmp->file[0]);
	free(new_args);
}

int main()
{
	t_prompt *pmp;
	pmp->file = malloc(100 * sizeof(char *));
	char *args[] = {"cat", "file1", ">", "file2", "<", "file3", "file4", "<<", "file5"};
	int n = sizeof(args) / sizeof(args[0]);
	remove_redirection_args(args, n, pmp);
	// if (pmp.file)
	// 	free(pmp.file);
	return 0;
}
