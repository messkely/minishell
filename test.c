#include <stdio.h>
#include <stdlib.h>

int	main()
{
	const char	*name;
	char		*value;

	name = "USER";
	value = getenv(name);
	if (value != NULL)
		printf("%s=%s\n", name, value);
	else
		printf("Environment variable %s not found.\n", name);
	return (0);
}

sq = 0;
dq = 0;

if ('\'' == c)
