#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(int argc, char **argv)
{
	t_progdata	p_data;
	void	*mlx;
	void	*win;
	t_data	img;

	if (argc == 2)
	{
		parsing(&p_data, argv);
		mlx = mlx_init();
		win = mlx_new_window(mlx, 1920, 1080, "cub3D");
		img.img = mlx_new_image(mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
		for (int i = 1; i < 1080 / 2; i++)
		{
			for (int j = 1; j < 1920 / 2; j++)
			{
				mlx_put_image_to_window(mlx, win, img.img, j, i);
			}
		}
		mlx_loop(mlx);
	}
}
