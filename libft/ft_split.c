/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:33:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/28 21:54:07 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strn(const char *s, char c)
{
	int	nbst;
	int	stcnt;

	nbst = 0;
	stcnt = 0;
	while (*s)
	{
		if (*s != c && stcnt == 0)
		{
			stcnt = 1;
			nbst++;
		}
		else if (*s == c)
		{
			stcnt = 0;
		}
		s++;
	}
	return (nbst);
}

static char	*nextstr(const char *str, int begin, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = malloc(sizeof(char) * (end - begin + 1));
	while (begin < end)
	{
		string[i] = str[begin];
		i++;
		begin++;
	}
	string[i] = '\0';
	return (string);
}

static char	**action(char **new, char const *s, char c)
{
	int		start;
	int		j;
	int		i;
	int		ss;

	start = -1;
	i = 0;
	j = 0;
	ss = ft_strlen(s);
	while (i <= ss)
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ss) && start >= 0)
		{
			new[j] = nextstr(s, start, i);
			start = -1;
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		nbstr;

	if (!s)
		return (NULL);
	nbstr = strn(s, c);
	if (!nbstr)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (nbstr + 1));
	if (!new)
		return (NULL);
	action(new, s, c);
	return (new);
}
