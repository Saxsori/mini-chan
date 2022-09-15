/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:15 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 05:11:00 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

char	*get_env_name(t_env_info *env_info)
{
	char	*name;
	char	*source;
	int		i;
	int		j;

	i = -1;
	source = ft_strdup \
	(env_info->exp_tools->main->first_split[env_info->exp_tools->index]);
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
		if (env_info->exp_tools->main->first_split \
		[env_info->exp_tools->index][j] == env->env_name[i])
			j++;
		else
			return (0);
	}
	return (1);
}

void	null_enval(t_env_info *env_info)
{
	env_info->env_value = NULL;
	env_info->value_len = 0;
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
		else
			null_enval(env_info);
	}
	else if (env_info->e_valid == 0)
	{
		env_info->env_value = get_env_name(env_info);
		env_info->value_len = ft_strlen(env_info->env_value);
	}
	else
	{
		if (env_info->e_valid == 'e')
		{
			env_info->env_value = ft_itoa(g_status);
			env_info->value_len = ft_strlen(env_info->env_value);
		}
		else
			null_enval(env_info);
	}
}
