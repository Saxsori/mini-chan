/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_find_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:10:32 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 05:11:07 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	find_env_first_node(t_env_info *env_info, t_mini_envar *temp)
{
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

/*
	// if (temp && !temp->next)
	// {
	// 	if (ft_strlen(temp->env_name) == env_info->name_len)
	// 	{
	// 		if (cmp_env_name(env_info, temp))
	// 		{
	// 			env_info->env_ptr = temp;
	// 			return (1);
	// 		}
	// 	}
	// }

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
	if (find_env_first_node(env_info, temp))
		return (1);
	return (0);
}
