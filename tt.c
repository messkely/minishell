#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_prompt
{
    char            **argv;
    char            **file;
    struct s_prompt *next;
}   t_prompt;

int ft_arglen(char **args)
{
    int i = 0;
    while (args[i])
        i++;
    return (i);
}

int count_valid_elements(char *args[], int n)
{
    int count = 0;
    int i = 0;
    while (i < n)
    {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 ||
            strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0)
            i++;
        else
            count++;
        i++;
    }
    return count;
}

char **rm_red_args(char *args[], int n, t_prompt *pmp)
{
    int new_size = count_valid_elements(args, n);
    char **new_args = (char **)malloc((new_size + 1) * sizeof(char *));
    int j = 0;
    int i = 0;
    int file_index = 0;

    while (i < n)
    {
        if (!strcmp(args[i], ">") || !strcmp(args[i], "<") ||
            !strcmp(args[i], ">>") || !strcmp(args[i], "<<"))
        {
            if (i + 1 < n)
            {
                pmp->file[file_index++] = strdup(args[i]);
                pmp->file[file_index++] = strdup(args[++i]);
            }
        }
        else
        {
            new_args[j++] = strdup(args[i]);
        }
        i++;
    }
    new_args[j] = NULL;
    pmp->file[file_index] = NULL;

    for (int k = 0; k < n; k++)
    {
        free(args[k]);
    }
    free(args);

    return new_args;
}

t_prompt *ft_lstnew(char *data)
{
    t_prompt *new;
    int i;

    new = malloc(sizeof(t_prompt));
    if (!new)
        return (NULL);
    new->argv = process_token(ft_strtrim(data, " "), ' ');
    if (!new->argv)
    {
        free(new);
        return (NULL);
    }
    i = 0;
    while (new->argv[i])
    {
        new->argv[i] = rm_escape_char(new->argv[i]);
        i++;
    }
    new->file = malloc(100 * sizeof(char *));
    if (!new->file)
    {
        // Free previously allocated argv
        for (int j = 0; new->argv[j]; j++)
            free(new->argv[j]);
        free(new->argv);
        free(new);
        return (NULL);
    }
    new->argv = rm_red_args(new->argv, ft_arglen(new->argv), new);

    for (int i = 0; new->argv[i]; i++)
        printf("%s ", new->argv[i]);
    printf("\n");

    for (int i = 0; new->file[i] != NULL; i++)
        printf("%s ", new->file[i]);
    printf("\n");
    printf("########################\n");

    new->next = NULL;
    return new;
}

void fill_stack(char **arr, t_prompt **pmp)
{
    int i = 0;
    while (arr[i])
    {
        t_prompt *new_node = ft_lstnew(arr[i]);
        if (new_node)
            ft_add_back(pmp, new_node);
        i++;
    }
}

void ft_free_prompt(t_prompt *pmp)
{
    while (pmp)
    {
        t_prompt *temp = pmp;
        pmp = pmp->next;
        for (int i = 0; temp->argv[i]; i++)
            free(temp->argv[i]);
        free(temp->argv);
        for (int i = 0; temp->file[i]; i++)
            free(temp->file[i]);
        free(temp->file);
        free(temp);
    }
}

void ft_parser(t_prompt **pmp)
{
    char **arr;
    char *input;

    while (1)
    {
        input = readline("minishell> ");
        if (input == NULL)
            break;
        arr = process_token(input, '|');
        fill_stack(arr, pmp);
        for (int i = 0; arr[i]; i++)
            free(arr[i]);
        free(arr);
        free(input);
    }
}

int main()
{
    t_prompt *prompt = NULL;

    ft_parser(&prompt);
    ft_free_prompt(prompt);
    return 0;
}
