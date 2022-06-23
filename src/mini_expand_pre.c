/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:11:56 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/23 18:24:27 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	find_name_size(t_env_info *env_info)
{
	int	i;

	i = env_info->i_start;
	while (++i < ft_strlen(env_info->exp_tools->main->first_split[env_info->exp_tools->index]))
	{
		if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\t')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\v')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == ' ')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '\0')
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 34)
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == 39)
			break ;
		else if (env_info->exp_tools->main->first_split[env_info->exp_tools->index][i] == '$')
			break ;
	}
	env_info->i_end = i - 1;
	env_info->name_len = (env_info->i_end - env_info->i_start) + 1;
}

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

char	*get_env_name(t_env_info *env_info)
{
	char	*name;
	char	*source;
	int		i;
	int		j;

	i = -1;
	source = ft_strdup(env_info->exp_tools->main->first_split[env_info->exp_tools->index]);
	name = (char *)malloc(sizeof(char) * (env_info->name_len + 2));
	j = env_info->i_start - 2;
	while (++i < env_info->name_len + 1)
		name[i] = source[++j];
	name[i] = '\0';
	free (source);
	return (name);
}

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
	else if (env_info->e_valid == 0)
	{
		env_info->env_value = get_env_name(env_info);
		env_info->value_len = ft_strlen(env_info->env_value);
	}
	else
	{
		env_info->env_value = NULL;
		env_info->value_len = 0;
	}
}

void	find_istart(t_env_info *env_info)
{
	char	c;

	c = env_info->exp_tools->main->first_split[env_info->exp_tools->index][env_info->e_index + 1];
	if (c == ' ' || c == '\t' || c == '\v' || c == 34 || c == 39 || c == '\0')
		env_info->i_start = env_info->e_index;
	else
		env_info->i_start = env_info->e_index + 1;
}

void	handle_1dollar_case(t_env_info *env_info)
{
	char	*line;

	line = ft_strdup(env_info->exp_tools->main->first_split[env_info->exp_tools->index]);
	if (env_info->e_valid != 0)
	{
		if (line[env_info->e_index + 1] == '\0' \
			|| line[env_info->e_index + 1] == '\v' \
			|| (line[env_info->e_index - 1] == '\v' \
			&& line[env_info->e_index + 1] == '\v') || \
			line[env_info->e_index + 1] == ' ')
		{
			env_info->env_value = (char *)malloc(sizeof(char) * 2);
			env_info->env_value[0] = '$';
			env_info->env_value[1] = '\0';
			env_info->value_len = 1;
			env_info->name_len = 1;
			env_info->i_end = env_info->e_index;
		}
	}
}

void	init_env_info(t_env_info *env_info, t_expand_tools *exp_tools, int i)
{
	env_info->exp_tools = exp_tools;
	env_info->e_pos = i;
	env_info->e_index = exp_tools->main->env_index[exp_tools->index][i];
	env_info->e_valid = exp_tools->main->exp_valid[exp_tools->index][i];
	env_info->i_start = env_info->e_index + 1;
	printf("old exp len %d\n", env_info->exp_tools->new_exp_len);
	find_istart(env_info);
	find_name_size(env_info);
	if (env_info->e_valid == 0 || !find_env(env_info))
		env_info->env_ptr = NULL;
	get_env_value(env_info);
	// if (env_info->env_value != NULL)
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
		if (exp_tools->env_info[i].env_ptr != NULL)
			printf("env_ptr_con %s\n", exp_tools->env_info[i].env_ptr->env_cont);
		printf("env_value %s\n", exp_tools->env_info[i].env_value);
		printf("value_len %d\n", exp_tools->env_info[i].value_len);
		exp_tools->new_exp_len -= exp_tools->env_info[i].name_len;
		exp_tools->new_exp_len += exp_tools->env_info[i].value_len;
		printf("\n");
	}
	printf("new_exp_len %d\n", exp_tools->new_exp_len);
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
			do_expand(&exp_tools);
			//free
		}
	}
}
