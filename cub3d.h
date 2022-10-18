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
}	t_map;

#endif