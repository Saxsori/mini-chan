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