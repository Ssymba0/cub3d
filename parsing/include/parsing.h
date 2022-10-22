/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:12:02 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:43:05 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../utils/include/str_utils.h"

typedef struct s_map
{
	char	**map;
	int		map_size;
	int		map_width;
}	t_map;

typedef struct s_textures
{
	char	**text;
	int		tex_size;
}	t_textures;

typedef struct s_progdata
{
	char		**data;
	int			size;
	t_map		m;
	t_textures	t;
}	t_progdata;

void	parse_textures(t_progdata *p, int size);
int		texture_errors(t_progdata *p);
void	get_map_width(t_progdata *p, int start);
void	parse_map(t_progdata *p, int start);
int		get_map_start_index(t_progdata *p);
void	data_parser(t_progdata *p, int fd);
int		valid_map(char **map, int size);
int		valid_map_content(char **map, int size);

#endif