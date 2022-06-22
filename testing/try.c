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

// void	handle_1dollar_case(t_env_info *env_info)
// {
// 	if (env_info->e_valid == 1 && env_info->name_len == 2)
// 	{
// 		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index] == '$')
// 		{
// 			if (check_e_index(env_info, (env_info->e_index + 1)))
// 			{
// 				env_info->env_value = (char *)malloc(sizeof(char) * 2);
// 				env_info->env_value[0] = '$';
// 				env_info->env_value[1] = '\0';
// 				env_info->value_len = 1;
// 				env_info->name_len = 1;
// 			}
// 		}
// 	}
// 	else if (env_info->e_valid == 0 && env_info->name_len == 1)
// 	{
// 		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index] == '$')
// 		{
// 			if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index + 1] == '\0')
// 			{
// 				env_info->value_len = 1;
// 				env_info->name_len = 1;
// 			}
// 		}
// 	}
// }


// int	is_there_envar(char *line)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < ft_strlen(line))
// 	{
// 		if (line[i] == '$')
// 			return (1);
// 	}
// 	return (0);
// }

// int	is_exp_valid(t_env_expand *exp_tools)
// {
// 	if (exp_tools->main->exp_valid[exp_tools->index][exp_tools->env_ord])
// 		return (1);
// 	return (0);
// }

// int	check_e_index(t_env_info *env_info, int i)
// {

// 	if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\t' && env_info->e_valid != 2)
// 		return (1);
// 	// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\v')
// 	// 	return (1);
// 	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ' ')
// 		return (1);
// 	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\0')
// 		return (1);
// 	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 34)
// 		return (1);
// 	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 39)
// 		return (1);
// 	// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '$')
// 	// 	return (1);
// 	return (0);
// }

// void	loop_init(t_env_expand *exp_tools, int op)
// {
// 	if (op == 1)
// 	{
// 		if (exp_tools->e != -1)
// 			exp_tools->e = -1;
// 	}
// 	if (op == 2)
// 	{
// 		exp_tools->e = -1;
// 		exp_tools->s += (exp_tools->name_len + 1);
// 	}
// 	if (op == 3)
// 	{
// 		if (exp_tools->e != -1)
// 			exp_tools->i--;
// 	}
// }
// /*
// 	// i = -1;
// 	// while (++i < exp_tools->new_len_exp)
// 	// 	printf("new_line %c, i%d\n", new_line[i], i);
// 	// printf("1check %c, i%d, k%d\n", new_line[i], i, k);
// 	// printf("2check %c, i%d, k%d\n", new_line[i], i, k);
// */	
// void	do_expand(t_env_expand *exp_tools)
// {
// 	char	*new_line;
// 	int		k = 0;
// 	int		j;
// 	// static	int i;
// 	// printf("%d do_expand(exp_tools)\n", exp_tools->new_len_exp);
// 	printf("new len size%d\n", exp_tools->new_len_exp);
// 	printf("%denv index\n", exp_tools->main->env_index[exp_tools->index][exp_tools->env_ord]);
// 	new_line = (char *)malloc(exp_tools->new_len_exp * sizeof(char) + 1);
// 	while (++exp_tools->i < exp_tools->new_len_exp)
// 	{
// 		if (exp_tools->main->env_index[exp_tools->index][exp_tools->env_ord] == k)
// 		{
// 			printf("1->i %d - k %d\n", exp_tools->i, k);
// 			j = -1;
// 			if (exp_tools->env_ptr != NULL)
// 			{	
// 				while (++j < ft_strlen(exp_tools->env_ptr->env_cont))
// 					new_line[exp_tools->i++] = exp_tools->env_ptr->env_cont[j];
// 			}
// 			else
// 				k++;
// 			k += exp_tools->name_len + 1;
// 			exp_tools->i--;
// 			printf("1->i %d - k %d\n", exp_tools->i, k);
// 		}
// 		else
// 		{
// 			// exp_tools->i++;
// 			if (exp_tools->main->first_split[exp_tools->index][k] != '\0')
// 				new_line[exp_tools->i] = exp_tools->main->first_split[exp_tools->index][k];
// 			printf("2->i %d - k %d\n", exp_tools->i, k);
// 			k++;
// 		}
// 	}
// 	new_line[exp_tools->i] = '\0';
// 	printf("%s\n", new_line);
// 	free (exp_tools->main->first_split[exp_tools->index]);
// 	if (new_line[0] != '\0')
// 		exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
// 	else
// 	{
// 		exp_tools->main->first_split[exp_tools->index] = malloc(sizeof(char));
// 		exp_tools->main->first_split[exp_tools->index][0] = '\0';
// 	}
// 	free (new_line);
// 	k = 0;
// 	exp_tools->i = -1;
// 	// int i = -1;
// 	// while (++i < exp_tools->new_len_exp)
// 	// 	printf("n%c\n", exp_tools->main->first_split[exp_tools->index][i]);
// 	printf("new_line %s\n", exp_tools->main->first_split[exp_tools->index]);
// }