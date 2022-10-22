/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:18:28 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:08:29 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/str_utils.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || \
	c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*dup_no_newline(char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*skip_whitespaces(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (s + i);
}

void	ft_bzero(void *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((char *)p)[i] = 0;
		i++;
	}
}
