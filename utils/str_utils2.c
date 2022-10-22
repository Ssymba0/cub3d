/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 08:50:31 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:40:58 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/str_utils.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 2);
	if (!buf)
		return (NULL);
	line = 0;
	while (read(fd, buf, 1) > 0)
	{
		buf[1] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(buf);
	return (line);
}

char	*dup_line_with_length(char *line, int length)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (i < length)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
