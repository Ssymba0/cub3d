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

void	map_parser(t_map *map, int fd)
{
	char	*line;

	map->map = malloc(sizeof(char *) * 1);
	map->map[0] = NULL;
	map->map_size = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->map = extend_tab(map->map, &map->map_size, line);
		line = get_next_line(fd);
	}
}


int	map_checker_types(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_size && (*map->map[i] != '1' && *map->map[i] != '0' && *map->map[i] != ' '))
	{
		if (strncmp(map->map[i], "NO ", 3) && strncmp(map->map[i], "SO ", 3) \
		&& strncmp(map->map[i], "WE ", 3) && strncmp(map->map[i], "EA ", 3) \
		&& strncmp(map->map[i], "F ", 2) && strncmp(map->map[i], "C ", 2))
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
	t_map	map;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (0);
		map_parser(&map, fd);
		int index = map_checker_types(&map);
		char **test = dup_tab_from_index_nospace(map.map, map.map_size, index);
		for (int i = 0; test[i]; i++)
			printf("%s", test[i]);
		// for (int i = 0; i < map.map_size; i++)
		// 	printf("line[%d] size= %d, line = %s\n", i + 1, line_size_no_space(map.map[i]), dup_line_nospace(map.map[i]));
		close(fd);
	}
	return (0);
}
