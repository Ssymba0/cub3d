/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:17:57 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:22:28 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	get_map_start_index(t_progdata *p)
{
	int		i;
	char	*no_sp;

	i = 0;
	p->t.tex_size = 0;
	no_sp = skip_whitespaces(p->data[i]);
	while (i < p->size && (*no_sp != '1' && *no_sp != '0'))
	{
		// if ((strncmp(no_sp, "NO ", 3) && strncmp(no_sp, "SO ", 3) \
		// && strncmp(no_sp, "WE ", 3) && strncmp(no_sp, "EA ", 3) \
		// && strncmp(no_sp, "F ", 2) && strncmp(no_sp, "C ", 2)) && *no_sp)
		// 	return (0);
		i++;
		if (*no_sp)
			p->t.tex_size++;
		no_sp = skip_whitespaces(p->data[i]);
	}
	return (i);
}

void	parse_map(t_progdata *p, int start)
{
	int	i;
	int	j;

	p->m.map = (char **)malloc(sizeof(char *) * (p->size - start + 1));
	if (!p->m.map)
		return ;
	i = start - 1;
	j = 0;
	while (++i < p->size)
	{
		p->m.map[j++] = dup_line_with_length(p->data[i], p->m.map_width);
	}
	p->m.map[j] = NULL;
	p->m.map_size = j;
}

void	get_map_width(t_progdata *p, int start)
{
	int	i;

	i = start;
	while (i < p->size)
	{
		if (p->m.map_width < (int)ft_strlen(p->data[i]))
			p->m.map_width = ft_strlen(p->data[i]);
		i++;
	}
}
