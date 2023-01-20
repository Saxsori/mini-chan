#include "../incl/mini_chan.h"

int main()
{
	char *str;
	char **split;
	int	i;

	str = ft_strdup("abrar");
	split = ft_split(str, 'r');
	i = -1;
	while (split[++i])
	{
		free(split[i]);
	}
	free(split);
	free(str);
}
