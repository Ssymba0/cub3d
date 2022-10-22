/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:16:39 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 09:29:23 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <mlx.h>
# include "./utils/include/str_utils.h"
# include "./parsing/include/parsing.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_imgs
{
	t_data	wall_img;
	t_data	floor_img;
	t_data	player_img;
}				t_imgs;

int		parsing(t_progdata *p_data, char **argv);
void	draw_map(t_mlx *m, t_imgs *imgs, t_progdata *p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	create_imgs(t_imgs *imgs, t_mlx *m);
void	init_mlx_struct(t_mlx *m, t_progdata *p);
void	ft_bzero(void *p, int n);
char	*skip_whitespaces(char *s);
char	*dup_no_newline(char *s);
int		ft_isspace(char c);
int		min(int a, int b);
char	**extend_tab(char **tab, int *size, char *elem);
void	free_tab(char **tab, int size);
char	*get_next_line(int fd);
char	*dup_line_with_length(char *line, int length);

#endif