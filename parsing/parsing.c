/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:58:04 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:27:58 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

int	parsing(t_progdata *p_data, char **argv)
{
	int	index;
	int	fd;

	fd = open(argv[1], O_RDONLY);
	index = 0;
	if (fd == -1)
		return (0);
	data_parser(p_data, fd);
	index = get_map_start_index(p_data);
	parse_textures(p_data, index);
	get_map_width(p_data, index);
	parse_map(p_data, index);
	if (texture_errors(p_data) || \
	!valid_map_content(p_data->m.map, p_data->m.map_size) \
	|| !valid_map(p_data->m.map, p_data->m.map_size))
	{
		printf("ERROR\n");
		return (0);
	}
	close(fd);
	return (1);
}
