/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:32:39 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/02 05:05:23 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? 1- replace the first with \t and then search for the second quote to
? close the first and replace it with quote
? 2- between the first and the second quote replace all the spaces with \v
? this is the way to not split the spaces inside the quote by then 
*/
void	find_scnd(t_shell_chan *main, char *line, int index)
{
	char	quote;

	quote = line[index];
	line[index] = '\t';
	while (++index < ft_strlen(line) + 1)
	{
		if (line[index] == ' ')
			line[index] = '\v';
		if (line[index] == quote)
		{
			line[index] = '\t';
			main->q_pars.begin = index;
			return ;
		}
	}
}

/*
? hold the first quote and send the line with the index to look
? 	for the second quote
*/
void	find_frst(t_shell_chan *main, char *line)
{
	while (++main->q_pars.begin < ft_strlen(line))
	{
		if (line[main->q_pars.begin] == 34 || line[main->q_pars.begin] == 39)
			find_scnd(main, line, main->q_pars.begin);
	}
}

/*
line length with no quotes
? count the length of the string without the closed quote
*/
int	line_len(char *line)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] != '\t')
			len++;
	}
	return (len);
}

/*
after checking of the quotes are valid (closed) then take them off
	and store the new one withput the quote
? 1- find first quote and from there find the second one
? 2- malloc with the new size
? 3- copy everything (the line without quotes)
?	in the string except the \t (the quote)
? 4- free the line from the first split which hold the 
?	old string
? 5- copy the new line without the quote in the first split string
? 6- free the new line
*/
int	quote_split(t_shell_chan *main, char *line, int i)
{
	char	*new_line;
	int		f;
	int		n;

	find_frst(main, line);
	new_line = (char *)malloc((line_len(line) + 1) * sizeof(char));
	f = -1;
	n = 0;
	while (++f < ft_strlen(line))
	{
		if (line[f] != '\t')
			new_line[n++] = line[f];
	}
	new_line[n] = '\0';
	free(main->first_split[i]);
	main->first_split[i] = ft_strdup(new_line);
	free(new_line);
	printf("%s - %d\n", main->first_split[i], ft_strlen(main->first_split[i]));
	return (1);
}
