#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main( void )
{
    char* cwd;
    char buff[PATH_MAX];

    cwd = getcwd(buff, PATH_MAX);
    if(cwd != NULL)
        printf("My working directory is %s\n", cwd);
    return (EXIT_SUCCESS);
}