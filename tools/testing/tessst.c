#include <stdio.h>

int	main ()
{
	int	i;
	char	str[5] = "abrar";
	str[2] = '\a';
	i = -1;
	while (++i < 5)
	{
		if (str[i] == '\a')
			printf("loool\n");
		printf ("(%c)\n", str[i]);
	}
}