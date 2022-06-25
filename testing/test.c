#include "../libft/libft.h"

int main(int ac, char **ag)
{
	char	*str;

	str = ft_strnstr(ag[1], "-n", ft_strlen(ag[1]));
	if (str)
		printf ("%s\n", str);
	else if (!str)
		printf ("error\n");
}