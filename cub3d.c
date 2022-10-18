#include "cub3d.h"

int	line_size_no_space(char *line);

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || \
	c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	line_size_no_space(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			j++;
		i++;
	}
	return (j);
}
void	free_tab(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
}

char	*dup_line_replace_space(char *line)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		if (line[i] == ' ')
			new[j] = '1';
		else
			new[j] = line[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	**dup_tab_from_index_nospace(char **tab, int size, int index)
{
	char	**new;
	int		i;
	int		j;

	i = index;
	new = (char **)malloc(sizeof(char *) * ((size - index) + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (i < size)
	{
		new[j++] = dup_line_replace_space(tab[i]);
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**extend_tab(char **tab, int *size, char *elem)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (*size + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < *size)
		new[i] = tab[i];
	new[i++] = elem;
	new[i] = NULL;
	(*size)++;
	free(tab);
	return (new);
}

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

void	map_parser(t_progdata *p, int fd)
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

int	map_checker_types(t_progdata *p)
{
	int		i;
	char	*new_line;
	char	*no_sp;

	i = 0;
	p->t.tex_size = 0;
	no_sp = skip_whitespaces(p->data[i]);
	while (i < p->size && (*no_sp != '1' && *no_sp != '0'))
	{
		new_line = strchr(p->data[i], '\n');
		if ((strncmp(no_sp, "NO ", 3) && strncmp(no_sp, "SO ", 3) \
		&& strncmp(no_sp, "WE ", 3) && strncmp(no_sp, "EA ", 3) \
		&& strncmp(no_sp, "F ", 2) && strncmp(no_sp, "C ", 2)) && !new_line)
			return (0);
		i++;
		if (*no_sp)
			p->t.tex_size++;
		no_sp = skip_whitespaces(p->data[i]);
	}
	return (i);
}

// int	map_checker_map(t_map *map, int index)
// {
// 	int		i;
// 	char	**map_nosp;

// 	i = index;
	
// }

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

int	texture_errors(t_progdata *p)
{
	enum{NO, SO, WE, EA, F, C};
	int	i;
	char a[6];

	ft_bzero(a, 6);
	i = -1;
	while (++i < p->t.tex_size)
	{
		if (!strncmp(p->data[i], "NO ", 3))
			a[NO]++;
		else if (!strncmp(p->data[i], "SO ", 3))
			a[SO]++;
		else if (!strncmp(p->data[i], "WE ", 3))
			a[WE]++;
		else if (!strncmp(p->data[i], "EA ", 3))
			a[EA]++;
		else if (!strncmp(p->data[i], "F ", 2))
			a[F]++;
		else if (!strncmp(p->data[i], "C ", 2))
			a[C]++;
	}
	i = -1;
	while (++i < 6)
		if (a[i] > 1)
			return (1);
	return (0);
}
void	parse_textures(t_progdata *p, int size)
{
	int	i;
	int	j;

	p->t.text = (char **)malloc(sizeof(char *) * (p->t.tex_size + 1));
	if (!p->t.text)
		return ;
	p->t.tex_size = size;
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (*skip_whitespaces(p->data[i]))
			p->t.text[j++] = skip_whitespaces(p->data[i]);
	}
	p->t.text[j] = NULL;
}

int	main(int argc, char **argv)
{
	t_progdata p_data;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (0);
		map_parser(&p_data, fd);
		int index = map_checker_types(&p_data);
		parse_textures(&p_data, index);
		for (int i = 0; i < p_data.t.tex_size; i++)
			printf("%s\n", p_data.t.text[i]);
		if (texture_errors(&p_data))
		{
			printf("Textures ERROR\n");
			return (0);
		}
		char **test = dup_tab_from_index_nospace(p_data.data, p_data.size, index);
		for (int i = 0; test[i]; i++)
			printf("%s", test[i]);
		// for (int i = 0; i < p_data.size; i++)
		// 	printf("%s", p_data.data[i]);
		close(fd);
	}
	return (0);
}
