/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:15:29 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 12:20:08 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_struct(t_mlx *m, t_progdata *p)
{
	m->width = 50 * p->m.map_width;
	m->height = 50 * p->m.map_size;
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, m->width, m->height, "cub3D");
}

void	init_img_data(t_data *data, t_mlx *m)
{
	data->img = mlx_new_image(m->mlx, m->width, m->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, &data->endian);
}

void	init_imgs(t_imgs *imgs, t_mlx *m)
{
	init_img_data(&imgs->wall_img, m);
	init_img_data(&imgs->floor_img, m);
	init_img_data(&imgs->player_img, m);
}

void	create_imgs(t_imgs *imgs, t_mlx *m)
{
	int	i;
	int	j;

	i = 0;
	init_imgs(imgs, m);
	while (i < 49)
	{
		j = 0;
		while (j < 49)
		{
			my_mlx_pixel_put(&imgs->wall_img, i, j, 0x00FF0000);
			my_mlx_pixel_put(&imgs->floor_img, i, j, 0x0000FF00);
			if ((i == 25 && j == 25))
			{
				my_mlx_pixel_put(&imgs->player_img, i, j, 0x000000FF);
				imgs->player_pixel_x = i;
				imgs->player_pixel_y = j;
			}
			else
				my_mlx_pixel_put(&imgs->player_img, i, j, 0x0000FF00);
			j++;
		}
		i++;
	}
}
