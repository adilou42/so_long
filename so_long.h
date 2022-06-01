/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:12:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/01 18:48:33 by ayakdi           ###   ########.fr       */
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

typedef struct s_player
{
	int	x;
	int y;
}	t_player;

typedef struct s_world
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	int		height;
	int		width;
}	t_world;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		count;
	t_world	map;
}	t_data;

typedef struct lst_map
{
	char	*line;
	size_t len;
	struct lst_map *next;
	char **carte;
}	t_map;