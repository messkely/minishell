#include <libc.h>

void	check_qoutes(char *s, char qoute)
{
	int i = 0;
	int flg = 1;
	int flg_q = 1;

	s = malloc(5);
	s[0] = '\'';
	s[1] = 'a';
	s[2] = 'c';
	s[3] = 'a';
	s[4] = '\0';
	s[5] = 'g';
	s[6] = 'g';
	s[7] = 'g';
	s[8] = 'g';
	s[9] = 'g';
	// printf("this is last char: %s\n", s);

	while (s[i])// 'kjh
	{
		if (s[i] == qoute)
		{
			flg = 0;
			i++;
			while (s[i] && s[i] != qoute)
				i++;
		}
		if (s[i] == qoute)
			flg = 1;
		
		// i++;
		printf("%d\n",i);
	}
	if (s[i] == '\0' && !flg)
	{
		printf("error");
		exit(1);
	}
	else
	{
		printf("all qoutes is closed");
		exit(0);
	}
}

int main()
{
	char *s = "";
	check_qoutes(s, '\'');
	// check_qoutes("\"'''\"", '\'');
	return (120);
}