/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:12:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/31 18:15:16 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_world
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	int		height;
	int		width;
	t_img	img;
}	t_world;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	// void	*img;
	int		count;
	t_img	img;
	t_world	map;
}	t_data;


typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

int	handle_no_event(void *data);
int	handle_input(int keysym, t_data *data);
void	img_pix_put(t_img *image, int x, int y, int color);

