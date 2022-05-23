/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:02 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:15:59 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int	i;
	char	*src2;
	char	*dst2;

	i = 0;
	src2 = (char *) src;
	dst2 = (char *) dst;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
