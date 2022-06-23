/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand_envar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:14:20 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/23 07:27:53 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_exp_loop(t_expand_tools *exp_tools)
{
	exp_tools->i = 0;
	exp_tools->s = -1;
	exp_tools->e = 0;
}

void	do_expand(t_expand_tools *exp_tools)
{
	char	*new_line;

	new_line = (char *)malloc((exp_tools->new_exp_len + 1) * sizeof(char));
	while (++exp_tools->s < ft_)
}