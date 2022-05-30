/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:04:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/29 14:13:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mini_chan.h"
#include <sys/types.h>
#include <dirent.h>
 
int	main ()
{
	DIR *dir;
	// struct dirent *entry;

	if ((dir = opendir("Make")) == NULL)
    	perror("opendir() error\n");
	else
		printf("success\n");
	return (0);
}