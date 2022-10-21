#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 	draw_map(t_mlx *m, t_imgs *imgs, t_progdata *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->m.map_size)
	{
		j = 0;
		while (j < p->m.map_width)
		{
			if (p->m.map[i][j] == '1')
				mlx_put_image_to_window(m->mlx, m->win, imgs->wall_img.img, j * 50, i * 50);
			else if (p->m.map[i][j] == '0')
				mlx_put_image_to_window(m->mlx, m->win, imgs->floor_img.img, j * 50, i * 50);
			else if (p->m.map[i][j] == 'N' || p->m.map[i][j] == 'S' || p->m.map[i][j] == 'E' || p->m.map[i][j] == 'W')
				mlx_put_image_to_window(m->mlx, m->win, imgs->player_img.img, j * 50, i * 50);
			j++;
		}
		i++;
	}
}
