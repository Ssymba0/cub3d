/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:28:39 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:28:53 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	check_no_dup_textures(char *a)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (a[i] != 1)
			return (1);
	}
	return (0);
}

int	texture_errors(t_progdata *p)
{
	int		i;
	char	a[6];

	enum {NO, SO, WE, EA, F, C};
	ft_bzero(a, 6);
	i = -1;
	while (++i < p->t.tex_size)
	{
		if (!strncmp(p->t.text[i], "NO ", 3))
			a[NO]++;
		else if (!strncmp(p->t.text[i], "SO ", 3))
			a[SO]++;
		else if (!strncmp(p->t.text[i], "WE ", 3))
			a[WE]++;
		else if (!strncmp(p->t.text[i], "EA ", 3))
			a[EA]++;
		else if (!strncmp(p->t.text[i], "F ", 2))
			a[F]++;
		else if (!strncmp(p->t.text[i], "C ", 2))
			a[C]++;
		else if (*skip_whitespaces(p->t.text[i]))
			return (1);
	}
	return (check_no_dup_textures(a));
}
