/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:58:04 by isabri            #+#    #+#             */
/*   Updated: 2022/10/21 13:25:17 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	map_checker_types(t_progdata *p)
{
	int		i;
	char	*no_sp;

	i = 0;
	p->t.tex_size = 0;
	no_sp = skip_whitespaces(p->data[i]);
	while (i < p->size && (*no_sp != '1' && *no_sp != '0'))
	{
		if ((strncmp(no_sp, "NO ", 3) && strncmp(no_sp, "SO ", 3) \
		&& strncmp(no_sp, "WE ", 3) && strncmp(no_sp, "EA ", 3) \
		&& strncmp(no_sp, "F ", 2) && strncmp(no_sp, "C ", 2)) && *no_sp)
			return (0);
		i++;
		if (*no_sp)
			p->t.tex_size++;
		no_sp = skip_whitespaces(p->data[i]);
	}
	return (i);
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
			return (0);
	}
	i = -1;
	while (++i < 6)
	{
		if (a[i] != 1)
			return (1);
	}
	return (0);
}

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

int	valid_map(char **map, int size)
{
	char	*line;
	char	*prev_line;
	int		i;
	int		j;

	i = -1;
	line = skip_whitespaces(map[0]);
	while (line[++i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (0);
	}
	prev_line = line;
	i = -1;
	line = skip_whitespaces(map[size - 1]);
	while (line[++i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return (0);
	}
	i = 1;
	while (i < size - 1)
	{
		line = skip_whitespaces(map[i]);
		j = line - map[i];
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

int	parsing(t_progdata *p_data, char **argv)
{
	int	index;
	int	fd;
	
	fd = open(argv[1], O_RDONLY);
	index = 0;
	if (fd == -1)
		return (0);
	data_parser(p_data, fd);
	index = map_checker_types(p_data);
	parse_textures(p_data, index);
	if (texture_errors(p_data))
	{
		printf("Textures ERROR\n");
		return (0);
	}
	get_map_width(p_data, index);
	parse_map(p_data, index);
	if (!valid_map_content(p_data->m.map, p_data->m.map_size))
	{
		printf("Map ERROR\n");
		return (0);
	}
	if (!valid_map(p_data->m.map, p_data->m.map_size))
	{
		printf("Map ERROR\n");
		return (0);
	}
	close(fd);
	return (1);
}
