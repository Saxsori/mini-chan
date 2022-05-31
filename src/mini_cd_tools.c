/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:14 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/31 04:31:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_doubslash(char *line)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '/')
			k++;
	}
	return (k);
}
