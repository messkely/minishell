#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
int status = system("ls -l");
if (status == -1) {
    perror("system");
    return 1;
}
if (WIFEXITED(status)) {
    printf("Command exited with status: %d\n", WEXITSTATUS(status));
} else {
    printf("Command did not exit successfully\n");
}
}