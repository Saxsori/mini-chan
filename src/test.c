# include <stdio.h>
#include <stdlib.h>

typedef struct mini
{
	int	kk;
	char *str;
}	t_mini;

void	jj(int *array)
{
	printf("%d\n", array + 1);
	// printf("%d\n", array->kk);
	// printf("%s\n", array->str);
	// printf("%s\n", array[1].str);
	// printf("%d\n", array[0].kk);
	// printf("%d\n", array[1].kk);
}

int main()
{
	int	i;
	// t_mini *bla;
	int	*array;
	
	i = -1;

	// bla = (t_mini *)malloc(sizeof(t_mini) * 2);
	array = (int *)malloc(sizeof(int));
	array[0] = 1;
	// bla[0].kk = 1;
	// bla[0].str = "hell";
	// bla[1].kk = 2;
	// bla[1].str = "holl";
	// jj(bla + 0);
	jj(array);

}
