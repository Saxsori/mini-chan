/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:01:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:17:42 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		strlen;
	int		ss1;
	int		ss2;

	if (!s1 || !s2)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)malloc(strlen * sizeof(char));
	if (!ret)
		return (NULL);
	else
	{
		ss1 = ft_strlen(s1);
		ss2 = ft_strlen(s2);
		ft_memcpy(ret, s1, ss1);
		ft_memcpy(ret + ss1, s2, ss2);
		ret[ss1 + ss2] = '\0';
	}
	return (ret);
}
