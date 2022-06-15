/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:28:36 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/15 03:57:06 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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

int	check_e_index(t_env_info *env_info, int i)
{

	if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\t' && env_info->e_valid != 2)
		return (1);
	// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\v')
	// 	return (1);
	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ' ')
		return (1);
	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\0')
		return (1);
	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 34)
		return (1);
	else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 39)
		return (1);
	// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '$')
	// 	return (1);
	return (0);
}
/*
? env_info->i_start points to the char when env name start after $
? so -- just for the loop
? and it ending end should be b4 these chars then clac the name len
*/
void	find_name_size(t_env_info *env_info)
{
	int	i;

	i = env_info->i_start;
	while (++i < ft_strlen(env_info->exp_tools->main->first_split[env_info->exp_tools->index]))
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\t' && env_info->e_valid != 2)
			break ;
		// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\v')
		// 	break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ' ')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\0')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 34)
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 39)
			break ;
		// else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '$')
		// 	break ;
	}
	printf("i %d\n", i);
	env_info->i_end = i - 1;
	env_info->name_len = env_info->i_end - env_info->i_start + 1;
}

/*
to compare the names
? starting from the index after $ to indicate the first letter of env name
? then check char by char if it was the same and increment the index
? if it was not te same then return 0
*/
int	cmp_env_name(t_env_info *env_info, t_mini_envar *env)
{
	int	i;
	int	j;

	i = -1;
	j = env_info->i_start;
	while (++i < env_info->name_len && j <= env_info->i_end)
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][j] == env->env_name[i])
			j++;
		else
			return (0);
	}
	return (1);
}

/*
// 	// if (!temp->next && !temp->next && temp)
// 	// {
// 	// 	if (ft_strlen(temp->env_name) == exp_tools->name_len)
// 	// 	{
// 	// 		if (cmp_env_name(exp_tools, temp))
// 	// 		{
// 	// 			exp_tools->env_ptr = temp;
// 	// 			return (1);
// 	// 		}
// 	// 	}
// 	// }
? to find whic env it is from the envar list 
? so take the head and search for the env name
? if they where the same length then 
? this the good start to compare the names
? if the names was the same then store it in the env_ptr 
? and return 1 back 
! NOTE that u r starting from the second var 
! not the first .. find a simple short way 
*/
int	find_env(t_env_info *env_info)
{
	t_mini_envar	*temp;

	temp = env_info->exp_tools->main->head_envar;
	while (temp->next)
	{
		if (ft_strlen(temp->env_name) == env_info->name_len)
		{
			if (cmp_env_name(env_info, temp))
			{
				env_info->env_ptr = temp;
				return (1);
			}
		}
		temp = temp->next;
	}
	if (temp && !temp->next)
	{
		if (ft_strlen(temp->env_name) == env_info->name_len)
		{
			if (cmp_env_name(env_info, temp))
			{
				env_info->env_ptr = temp;
				return (1);
			}
		}
	}
	return (0);
}

char	*get_env_name(t_env_info *env_info, int op)
{
	char	*name;
	char	*source;
	int		i;
	int		j;

	i = -1;
	name = NULL;
	source = ft_strdup(env_info->exp_tools->main->first_split[env_info->exp_tools->index]);
	if (op == 2)
	{
		name = (char *)malloc(sizeof(char) * (env_info->name_len + 1));
		j = env_info->i_start - 1;
		if (source[env_info->i_start] != '\0')
		{
			while (++i < env_info->name_len)
				name[i] = source[++j];
			name[i] = '\0';
		}
		else
		{
			free(name);
			name = NULL;
		}
	}
	else if (op == 0)
	{
		name = (char *)malloc(sizeof(char) * (env_info->name_len + 2));
		j = env_info->i_start - 2;
		while (++i < env_info->name_len + 1)
			name[i] = source[++j];
		name[i] = '\0';
	}
	free (source);
	return (name);
}

/*
- when var is valid in the env list
	-> but the content is empty
	-> the content is not empty
- when env is invlaid
	-> MODE 2 case $"var" or $'var'
	-> MODE 0 case '$var'
*/
void	get_env_value(t_env_info *env_info)
{
	if (env_info->env_ptr)
	{
		if (env_info->env_ptr->env_cont[0] != '\0')
		{
			env_info->env_value = ft_strdup(env_info->env_ptr->env_cont);
			env_info->value_len = ft_strlen(env_info->env_value);
		}
	}
	else if (env_info->e_valid == 2 || env_info->e_valid == 0)
	{
		if (env_info->e_valid == 2)
			env_info->env_value = get_env_name(env_info, 2);
		else if (env_info->e_valid == 0)
			env_info->env_value = get_env_name(env_info, 0);
		if (env_info->env_value != NULL)
			env_info->value_len = ft_strlen(env_info->env_value);
		else
			env_info->value_len = 0;
	}
	else
	{
		env_info->env_value = NULL;
		env_info->value_len = 0;
	}
}

void	handle_1dollar_case(t_env_info *env_info)
{
	if (env_info->e_valid == 1 && env_info->name_len == 2)
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index] == '$')
		{
			if (check_e_index(env_info, (env_info->e_index + 1)))
			{
				env_info->env_value = (char *)malloc(sizeof(char) * 2);
				env_info->env_value[0] = '$';
				env_info->env_value[1] = '\0';
				env_info->value_len = 1;
				env_info->name_len = 1;
			}
		}
	}
	else if (env_info->e_valid == 0 && env_info->name_len == 1)
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index] == '$')
		{
			if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index + 1] == '\0')
			{
				env_info->value_len = 1;
				env_info->name_len = 1;
			}
		}
	}
}

/*
* e_pos .. the position of the env to know which env
* e_index .. the index of the $
* e_valid .. to check if we can expand or not
* i_start .. the index of the var name where to it start

* .. find name size ..
* i_end .. the index of the var name where it should end
* name_len .. using i_start and i_name -> cal the name length

* .. find env ..
* env_ptr .. the ptr of the node of the env using name_len i_end and i_start

* env_value .. the value of the env using the env_ptr and taking the content
* value_len .. the length of the value to add to the main len by then
*/
void	init_env_info(t_env_info *env_info, t_expand_tools *exp_tools, int i)
{
	env_info->exp_tools = exp_tools;
	printf("line %s \n", env_info->exp_tools->main->first_split[exp_tools->index]);
	env_info->e_pos = i;
	env_info->e_index = exp_tools->main->env_index[exp_tools->index][i];
	env_info->e_valid = exp_tools->main->exp_valid[exp_tools->index][i];
	env_info->i_start = env_info->e_index + 1;
	env_info->name_len = exp_tools->main->env_n_len[exp_tools->index][i];
	env_info->i_end = (env_info->i_start - 1) + env_info->name_len;
	printf("first len %d\n", exp_tools->main->env_n_len[exp_tools->index][i]);
	if (exp_tools->main->env_n_len[exp_tools->index][i] == 0)
	{
		printf("here\n");
		find_name_size(env_info);
	}
	if (env_info->e_valid == 2 || env_info->e_valid == 0 || !find_env(env_info))
		env_info->env_ptr = NULL;
	get_env_value(env_info);
	if (env_info->env_value != NULL || env_info->e_valid != 2)
		env_info->name_len++;
	handle_1dollar_case(env_info);
}

void	start_expand(t_expand_tools *exp_tools)
{
	int	i;

	i = -1;
	while (++i < exp_tools->env_num)
		init_env_info(&exp_tools->env_info[i], exp_tools, i);
	i = -1;
	while (++i < exp_tools->env_num)
	{
		printf("pos %d\n", exp_tools->env_info[i].e_pos);
		printf("index %d\n", exp_tools->env_info[i].e_index);
		printf("valid %d\n", exp_tools->env_info[i].e_valid);
		printf("i_start %d\n", exp_tools->env_info[i].i_start);
		printf("i_end %d\n", exp_tools->env_info[i].i_end);
		printf("name_len %d\n", exp_tools->env_info[i].name_len);
		// if (exp_tools->env_info[i].env_ptr != NULL)
		// 	printf("env_ptr_con %s\n", exp_tools->env_info[i].env_ptr->env_cont);
		// printf("env_value %s\n", exp_tools->env_info[i].env_value);
		// printf("value_len %d\n", exp_tools->env_info[i].value_len);
		printf("\n");
	}
}

void	expand_envar(t_shell_chan *main)
{
	t_expand_tools	exp_tools;
	int				i;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_expand_tools(&exp_tools, main, i);
		if (exp_tools.env_num > 0)
		{
			start_expand(&exp_tools);
			free (exp_tools.env_info);
		}
	}
}
