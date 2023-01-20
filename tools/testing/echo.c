
# include "../mini_chan.h"

int main ()
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 4);
	arg[3] = NULL;
	arg[0] = ft_strdup("no");
	arg[1] = malloc(sizeof(char));
	arg[2] = ft_strdup("nla");
	int i;
	i = -1;
	while (arg[++i])
		printf("%s ", arg[i]);
	printf("\n");
}
