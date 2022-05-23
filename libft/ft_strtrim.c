/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:06:59 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:13:20 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*sf;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	sf = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!sf)
		return (NULL);
	i = 0;
	while (start < end)
	{
		sf[i] = s1[start];
		i++;
		start++;
	}
	sf[i] = '\0';
	return (sf);
}
