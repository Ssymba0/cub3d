/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:28:14 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 11:12:47 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		return (1);
	}
	return (0);
}

void	draw_map(t_mlx *m, t_imgs *imgs, t_progdata *p)
{
	int			i;
	int			j;

	i = 0;
	while (i < p->m.map_size)
	{
		j = 0;
		while (j < p->m.map_width)
		{
			if (p->m.map[i][j] == '1')
				mlx_put_image_to_window(m->mlx, m->win, \
				imgs->wall_img.img, j * 50, i * 50);
			else if (p->m.map[i][j] == '0')
				mlx_put_image_to_window(m->mlx, m->win, \
				imgs->floor_img.img, j * 50, i * 50);
			else if (is_player(p->m.map[i][j]))
				mlx_put_image_to_window(m->mlx, m->win, \
				imgs->player_img.img, j * 50, i * 50);
			j++;
		}
		i++;
	}
}
