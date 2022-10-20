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

int	parsing(t_progdata *p_data, char **argv);

#endif