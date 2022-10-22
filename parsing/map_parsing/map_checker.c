/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:21:39 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:39:42 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_map_char(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' \
	|| c == 'E')
		return (1);
	return (0);
}

int	is_map_char_w_walls(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' \
	|| c == 'E' || c == '1')
		return (1);
	return (0);
}

int	valid_map_content(char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_map_char_w_walls(map[i][j]) && !ft_isspace(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_top_down(char **map, int size)
{
	int		i;
	char	*line;

	i = -1;
	line = skip_whitespaces(map[0]);
	while (line[++i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (0);
	}
	i = -1;
	line = skip_whitespaces(map[size - 1]);
	while (line[++i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (0);
	}
	return (1);
}

int	valid_map(char **map, int size)
{
	int		i;
	int		j;

	i = 1;
	if (!check_top_down(map, size))
		return (0);
	while (i < size - 1)
	{
		j = skip_whitespaces(map[i]) - map[i];
		while (map[i][j])
		{
			if (is_map_char(map[i][j]))
			{
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' \
				|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
