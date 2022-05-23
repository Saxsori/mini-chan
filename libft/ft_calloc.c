/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrar <abrar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:46:12 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/21 14:16:22 by abrar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int count, int size)
{
	void	*pointer;

	pointer = malloc(count * size);
	if (pointer == NULL)
	{
		return (NULL);
	}
	else
	{
		ft_memset (pointer, '\0', count * size);
		return (pointer);
	}
}
