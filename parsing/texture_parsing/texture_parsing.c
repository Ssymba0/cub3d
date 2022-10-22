/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:21:05 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:21:16 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	parse_textures(t_progdata *p, int size)
{
	int	i;
	int	j;

	p->t.text = (char **)malloc(sizeof(char *) * (p->t.tex_size + 1));
	if (!p->t.text)
		return ;
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (*skip_whitespaces(p->data[i]))
			p->t.text[j++] = skip_whitespaces(p->data[i]);
	}
	p->t.text[j] = NULL;
	p->t.tex_size = j;
}
