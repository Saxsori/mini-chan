/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:57:57 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:13:02 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		cc;

	i = 0;
	cc = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			cc = i;
		}
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else if (cc == -1)
		return (NULL);
	else
		return ((char *)s + cc);
}
