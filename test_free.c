# include <stdio.h>
# include <stdlib.h>

// void	free_ptr(void **ptr)
// {
// 	free(*ptr);
// 	*ptr = NULL;
// }
void	free_ptr(void ***ptr)
{
	int	i;

	i = -1;
	while (++i < 2)
		free(ptr[i]);
		printf("hgfhg\n");
	free(ptr);
	ptr = NULL;
}
// void	free_ptr(void *ptr)
// {
// 	free(ptr);
// 	ptr = NULL;
// }

int	main()
{
	char	**str;
	// char	*str;

	str = malloc(sizeof(char *) * 2);
	// str = malloc(sizeof(char) * 2);
	str[0] = malloc(sizeof(char) * 2);
	str[0][0] = 'l';
	str[0][1] = '\0';
	str[1] = NULL;
	// str[0] = 'j';
	// str[1] = '\0';
	printf("%s\n", str[0]);
	// printf("%s\n", str);
	// free_ptr((void **)&str);
	free_ptr((void ***)&str);

	// free_ptr(str);
	if (!str)
		printf("1lala\n");
		// str = NULL;
	// printf("%s\n", str[0]);
}
