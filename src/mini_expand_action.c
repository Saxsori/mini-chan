/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:14:20 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 07:25:02 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_exp_loop(t_expand_tools *exp_tools)
{
	exp_tools->i = 0;
	exp_tools->i_s = -1;
	exp_tools->pos = 0;
}

/*
	// printf("i %d  -- len %d\n", exp_tools->i, exp_tools->new_exp_len + 1);
	! You have added this condition
	if (exp_tools->pos + 1 < exp_tools->env_num)
			exp_tools->pos++;
*/
void	do_expand(t_expand_tools *exp_tools)
{
	char	*new_line;

	init_exp_loop(exp_tools);
	new_line = (char *)malloc((exp_tools->new_exp_len + 1) * sizeof(char));
	while (++exp_tools->i_s < ft_strlen(exp_tools->main->first_split[exp_tools->index]))
	{
		if (exp_tools->main->env_index[exp_tools->index][exp_tools->pos] == exp_tools->i_s)
		{
			exp_tools->i_e = -1;
			if (exp_tools->env_info[exp_tools->pos].env_value != NULL)
			{
				while (++exp_tools->i_e < ft_strlen(exp_tools->env_info[exp_tools->pos].env_value))
					new_line[exp_tools->i++] = exp_tools->env_info[exp_tools->pos].env_value[exp_tools->i_e];
			}
			exp_tools->i_s += (exp_tools->env_info[exp_tools->pos].name_len - 1);
			if (exp_tools->pos + 1 < exp_tools->env_num)
				exp_tools->pos++;
		}
		else
			new_line[exp_tools->i++] = exp_tools->main->first_split[exp_tools->index][exp_tools->i_s];
	}
	new_line[exp_tools->i] = '\0';
	free(exp_tools->main->first_split[exp_tools->index]);
	exp_tools->main->first_split[exp_tools->index] = ft_strdup(new_line);
	free(new_line);
}

/*
*/
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
		printf("\n");
		exp_tools->new_exp_len -= exp_tools->env_info[i].name_len;
		exp_tools->new_exp_len += exp_tools->env_info[i].value_len;
	}
	printf("new_exp_len %d\n", exp_tools->new_exp_len);
}

/*

			printf("new line %s\n", main->first_split[i]);
*/
void	expand_envar(t_shell_chan *main)
{
	t_expand_tools	exp_tools;
	int				i;
	int				k;

	i = -1;
	while (++i < main->cmd_num)
	{
		init_expand_tools(&exp_tools, main, i);
		if (exp_tools.env_num > 0)
		{
			start_expand(&exp_tools);
			do_expand(&exp_tools);
			k = -1;
			while (++k < exp_tools.env_num)
			{
				if (exp_tools.env_info[k].env_value)
					free_ptr((void **)&exp_tools.env_info[k].env_value);
			}
			if (exp_tools.env_info)
				free_ptr((void **)&exp_tools.env_info);
		}
	}
}
