// #include "minishell.h"

int count_valid_elements(char *args[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0) {
            i++;
        } else {
            count++;
        }
    }
    return count;
}

void remove_redirection_args(char *args[], int n, t_prompt *pmp) {
    int new_size = count_valid_elements(args, n);
    char **new_args = (char **)malloc(new_size * sizeof(char *));
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        if (!strcmp(args[i], ">") || !strcmp(args[i], "<") || !strcmp(args[i], ">>") || !strcmp(args[i], "<<")) {
            // Concatenate the redirection symbol and the next argument to pmp->file
            pmp->file = ft_strjoin(pmp->file, args[i]);
            pmp->file = ft_strjoin(pmp->file, " ");
            pmp->file = ft_strjoin(pmp->file, args[++i]);
            pmp->file = ft_strjoin(pmp->file, " ");
        } else {
            new_args[j++] = args[i];
        }
    }

    for (int i = 0; i < new_size; i++) {
        printf("%s ", new_args[i]);
    }
    printf("\n");

    // Print the concatenated file string
    printf("file: %s\n", pmp->file);

    // Free allocated memory
    free(new_args);
}

int main() {
    t_prompt pmp;
    pmp.file = NULL; // Initialize pmp.file to NULL

    char *args[] = {"cat", "file1", ">", "file2", "<", "file3", "file4", "<<", "file5"};
    int n = sizeof(args) / sizeof(args[0]);

    remove_redirection_args(args, n, &pmp);

    // Free allocated memory for pmp.file
    if (pmp.file) {
        free(pmp.file);
    }

    return 0;
}
