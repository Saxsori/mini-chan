/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:15 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/29 13:25:12 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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
		printf("bro\n");
		if (env_info->e_valid == 'e')
		{
			env_info->env_value = ft_itoa(g_status);
			printf("itoa %s\n", env_info->env_value);
			env_info->value_len = ft_strlen(env_info->env_value);
		}
		else
		{
			env_info->env_value = NULL;
			env_info->value_len = 0;
		}
	}
}
