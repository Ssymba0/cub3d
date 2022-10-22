/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:05:27 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:15:13 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	data_parser(t_progdata *p, int fd)
{
	char	*line;

	p->data = malloc(sizeof(char *) * 1);
	p->data[0] = NULL;
	p->size = 0;
	line = get_next_line(fd);
	while (line)
	{
		p->data = extend_tab(p->data, &p->size, line);
		line = get_next_line(fd);
	}
}
