/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:52:13 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:15:42 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*result;
	int				i;
	unsigned char	a;

	i = 0;
	result = (unsigned char *)s;
	a = (unsigned char)c;
	while (i < n)
	{
		if (result[i] == a)
		{
			return (result + i);
		}
		i++;
	}
	return (NULL);
}
