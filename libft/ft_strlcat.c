/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:17:28 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:12:03 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, int dstsize)
{
	int	srcl;
	int	dstl;

	srcl = ft_strlen(src);
	dstl = ft_strlen(dst);
	if (dstl > dstsize)
	{
		dstl = dstsize;
	}
	else if (dstl == dstsize || dstsize == 0)
	{
		return (dstl + srcl);
	}
	else if (srcl < dstsize - dstl)
	{
		ft_memcpy(dst + dstl, src, srcl + 1);
	}
	else
	{
		ft_memcpy(dst + dstl, src, dstsize - dstl - 1);
		dst [dstsize - 1] = '\0';
	}
	return (dstl + srcl);
}
