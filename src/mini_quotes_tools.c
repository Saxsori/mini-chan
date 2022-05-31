/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:23:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/31 18:15:05 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_qt_valid(t_mini_cmd *cmd)
{
	while
}

int	quotes_parser(t_shell_chan *main)
{
	init_mini_quotes(main);
	if (is_qt_valid(main))
	{
		printf("1\n");
		return (1);
	}
	else
	{
		printf("0\n");
		return (0);
	}
}
