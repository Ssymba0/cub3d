/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabri <isabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:15 by isabri            #+#    #+#             */
/*   Updated: 2022/10/21 13:11:16 by isabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_progdata	p_data;
	t_mlx		m;
	t_imgs		imgs;

	if (argc == 2)
	{
		if (!parsing(&p_data, argv))
			return (0);
		init_mlx_struct(&m, &p_data);
		create_imgs(&imgs, &m);
		draw_map(&m, &imgs, &p_data);
		mlx_loop(m.mlx);
	}
}
