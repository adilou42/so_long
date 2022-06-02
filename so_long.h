/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:12:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/02 20:24:32 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./mlx/mlx.h"
// #include "Libft_42/libft.h"
#include "GNL/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

typedef struct s_vars
{
	void *mlx_ptr;
	void	*win_ptr;
}	t_mlx;
typedef struct coordonne
{
	int	x;
	int	y;
}	t_Coord;

typedef struct s_player
{
	int dir;
	t_Coord coord;
}	t_player;


typedef struct s_world
{
	char	**map;
	void	*wall;
	void	*floor;
	void	*perso;
	void	*collectible;
	void	*exit;
	int		height;
	int		width;
	int		item_count;
	int		move_count;
	t_player	*player;
	t_mlx	*mlx;
}	t_world;

typedef struct s_data
{
	int		count;
	t_world	img;
}	t_data;

typedef struct lst_map
{
	char	*line;
	size_t len;
	struct lst_map *next;
	char **carte;
}	t_map;