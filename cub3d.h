#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <mlx.h>
# include "get_next_line.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_map
{
	char	**map;
	int		map_size;
	int		map_width;
}	t_map;

typedef struct	s_textures
{
	char	**text;
	int		tex_size;
}	t_textures;

typedef struct	s_progdata
{
	char		**data;
	int			size;
	t_map		m;
	t_textures	t;
}	t_progdata;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_imgs
{
	t_data	wall_img;
	t_data	floor_img;
	t_data	player_img;
}				t_imgs;

int		parsing(t_progdata *p_data, char **argv);
void 	draw_map(t_mlx *m, t_imgs *imgs, t_progdata *p);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	create_imgs(t_imgs *imgs, t_mlx *m);
void	init_mlx_struct(t_mlx *m, t_progdata *p);

#endif