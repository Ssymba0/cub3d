#include "cub3d.h"

int	line_size_no_space(char *line);

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


int	map_checker_types(t_progdata *p)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < p->size && (*p->data[i] != '1' && *p->data[i] != '0'))
	{
		new_line = strchr(p->data[i], '\n');
		if ((strncmp(p->data[i], "NO ", 3) && strncmp(p->data[i], "SO ", 3) \
		&& strncmp(p->data[i], "WE ", 3) && strncmp(p->data[i], "EA ", 3) \
		&& strncmp(p->data[i], "F ", 2) && strncmp(p->data[i], "C ", 2)) && !new_line)
			return (0);
		i++;
	}
	return (i);
}

// int	map_checker_map(t_map *map, int index)
// {
// 	int		i;
// 	char	**map_nosp;

// 	i = index;
	
// }

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
		char **test = dup_tab_from_index_nospace(p_data.data, p_data.size, index);
		// for (int i = 0; test[i]; i++)
		// 	printf("%s", test[i]);
		for (int i = 0; i < p_data.size; i++)
			printf("%s", p_data.data[i]);
		close(fd);
	}
	return (0);
}
