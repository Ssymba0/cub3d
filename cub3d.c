/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:15 by isabri            #+#    #+#             */
/*   Updated: 2022/10/22 13:48:07 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
typedef struct d
{
	t_progdata	*p_data;
	t_mlx		*m;
	t_imgs		*imgs;
} d;

int move_up(int key_code, d *dt)
{
	printf("player_y = %d, player_x = %d\n", dt->imgs->player_pixel_y, dt->imgs->player_pixel_x);
	if (key_code == 13)
	{
		my_mlx_pixel_put(&dt->imgs->player_img, dt->imgs->player_pixel_x, dt->imgs->player_pixel_y, 0xFF0000);
		if (dt->imgs->player_pixel_y > 0)
			dt->imgs->player_pixel_y--;
		my_mlx_pixel_put(&dt->imgs->player_img, dt->imgs->player_pixel_x, dt->imgs->player_pixel_y, 0x00FF00);
	}
	mlx_destroy_image(dt->m->mlx, dt->imgs->player_img.img);
	mlx_put_image_to_window(dt->m->mlx, dt->m->win, dt->imgs->player_img.img, dt->imgs->player_pixel_x * 50, dt->imgs->player_pixel_y * 50);
	return (0);
}

void	get_player_position(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->map[i])
	{
		j = 0;
		while (m->map[i][j])
		{
			if (is_player(m->map[i][j]))
			{
				m->player_x = j;
				m->player_y = i;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_progdata	p_data;
	t_mlx		m;
	t_imgs		imgs;
	d data;
	
	data.p_data = &p_data;
	data.m = &m;
	data.imgs = &imgs;
	if (argc == 2)
	{
		if (!parsing(&p_data, argv))
			return (0);
		init_mlx_struct(&m, &p_data);
		create_imgs(&imgs, &m);
		draw_map(&m, &imgs, &p_data);
		mlx_key_hook(m.win, move_up, &data);
		mlx_loop(m.mlx);
	}
}
