/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:28:36 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/06 04:07:59 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_there_envar(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '$')
			return (1);
	}
	return (0);
}

int	is_exp_valid(t_env_expand *exp_tools)
{
	if (exp_tools->main->exp_valid[exp_tools->index][exp_tools->env_ord])
		return (1);
	return (0);
}

/*
exp_tools->start points to the char when env name start after $
so -- just for the loop
*/
void	find_name_size(t_env_expand *exp_tools)
{
	int	i;

	i = exp_tools->start;
	while (++i < ft_strlen(exp_tools->main->first_split[exp_tools->index]))
	{
		if (exp_tools->main->first_split[exp_tools->index][i] == '\t')
			break ;
		else if (exp_tools->main->first_split[exp_tools->index][i] == '\v')
			break ;
		else if (exp_tools->main->first_split[exp_tools->index][i] == ' ')
			break ;
		else if (exp_tools->main->first_split[exp_tools->index][i] == '\0')
			break ;
		else if (exp_tools->main->first_split[exp_tools->index][i] == 34)
			break ;
		else if (exp_tools->main->first_split[exp_tools->index][i] == 39)
			break ;
	}
	exp_tools->end = --i;
	exp_tools->name_len = exp_tools->end - exp_tools->start + 1;
}

int	cmp_env_name(t_env_expand *exp_tools, t_mini_envar *env)
{
	int	i;

	i = -1;
	while (++i < exp_tools->name_len && exp_tools->start <= exp_tools->end)
	{
		if (exp_tools->main->first_split[exp_tools->index][exp_tools->start] == env->env_name[i])
			exp_tools->start++;
		else
			return (0);
	}
	return (1);
}

/*
	// if (!temp->next && !temp->next && temp)
	// {
	// 	if (ft_strlen(temp->env_name) == exp_tools->name_len)
	// 	{
	// 		if (cmp_env_name(exp_tools, temp))
	// 		{
	// 			exp_tools->env_ptr = temp;
	// 			return (1);
	// 		}
	// 	}
	// }
*/
int	find_env(t_env_expand *exp_tools)
{
	t_mini_envar	*temp;

	temp = exp_tools->main->head_envar;
	while (temp->next)
	{
		if (ft_strlen(temp->env_name) == exp_tools->name_len)
		{
			if (cmp_env_name(exp_tools, temp))
			{
				exp_tools->env_ptr = temp;
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	is_envar(t_env_expand *exp_tools, int i)
{
	exp_tools->start = ++i;
	find_name_size(exp_tools);
	// printf("%d\n%d\n%d\n", exp_tools->start, exp_tools->end, exp_tools->name_len);
	if (find_env(exp_tools))
		return (1);
	return (0);
}

void	start_expand(t_env_expand *exp_tools)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(exp_tools->main->first_split[exp_tools->index]))
	{
		re_init_env_expand(exp_tools);
		if (exp_tools->main->first_split[exp_tools->index][i] == '$')
		{
			// printf("%s - ", exp_tools->main->first_split[exp_tools->index]);
			// printf("%d\n", i);
			if (is_exp_valid(exp_tools))
			{
				// printf("%d, is_exp_vaild\n", exp_tools->env_ord);
				if (is_envar(exp_tools, i))
				{
					printf("old len%d\n",exp_tools->new_len_exp);
					exp_tools->new_len_exp += ft_strlen(exp_tools->env_ptr->env_cont) - 1;
					exp_tools->new_len_exp -= exp_tools->name_len;
					printf("new len%d\n",exp_tools->new_len_exp);
					do_expand(exp_tools);
				}
			}
			exp_tools->env_ord++;
		}
	}
}

void	expand_envar(t_shell_chan *main)
{
	t_env_expand	exp_tools;
	int				i;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_env_expand(&exp_tools, main, i);
		if (is_there_envar(main->first_split[i]))
			start_expand(&exp_tools);
	}
}
