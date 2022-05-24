/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:12:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/24 14:51:19 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	int		count;
}	t_data;

typedef struct	s_map {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_map;

int	handle_no_event(void *data);
int	handle_input(int keysym, t_data *data);
