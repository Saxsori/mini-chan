/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:28:36 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/05 02:17:53 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mini_chan.h"

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

// int	is_exp_vaild(t_env_expand *env_expand)
// {
// 	if (env_expand->main->exp_valid[env_expand->index][env_expand->env_ord])
// }

// void	start_expand(t_env_expand *env_expand)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < ft_strlen(env_expand->main->first_split[env_expand->index]))
// 	{
// 		if (env_expand->main->first_split[env_expand->index][i] == '$')
// 		{
// 			if (is_exp_valid(env_expand))
			
// 		}
// 	}
// }

// void	expand_envar(t_shell_chan *main)
// {
// 	t_env_expand	env_exp;
// 	int				i;

// 	i = -1;
// 	while (++i < main->cmd_num)
// 	{
// 		init_env_expand(&env_exp, main, i);
// 		if (is_there_envar(main->first_split[i]))
// 		{
// 			start_expand(&env_exp);
// 		}
// 	}
// }
