#include "mini_chan.h"

char	*ft_strchr(const char *s, int c, int op)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)s;
	while (result[i] != '\0' && result[i] != (char) c)
		i++;
	if (op == 1)
	{
		if (result[i] == (char)c)
			return (result + i);
	}
	else if (op == 2)
	{
		if (result[i] == (char)c)
			return (result + (i + 1));
	}
	return (NULL);
}

int main ()
{
	char *str;

	str = ft_strchr("djh=f", '=', 2);
	printf("%s\n", str);
}