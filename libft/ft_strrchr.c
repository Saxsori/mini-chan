/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:57:57 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/25 13:22:43 by aaljaber         ###   ########.fr       */
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
	printf ("%d %d\n", cc, i);
	if (c == '\0')
		return ((char *)s + i);
	else if (cc == -1)
		return (NULL);
	else
		return ((char *)s + cc);
}
