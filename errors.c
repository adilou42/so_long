/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:46:04 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/10 18:17:18 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_mlx_error(char **map)
{
	free_map(map);
	write(2, "Error mlx\n", 10);
	exit(EXIT_FAILURE);
}

void	print_error(t_map *lmap, int nb)
{
	ft_lstclear(&lmap);
	if (nb == 2)
	{
		write(2, "Error missing exit\n", 19);
		exit(EXIT_FAILURE);
	}
	else if (nb == 3)
	{
		write(2, "Error missing player\n", 21);
		exit(EXIT_FAILURE);
	}
	else if (nb == 4)
	{
		write(2, "Error missing collectible\n", 26);
		exit(EXIT_FAILURE);
	}
	print_error_2(nb);
}

void	print_error_2(int nb)
{
	if (nb == 5)
	{
		write(2, "Error invalid file\n", 19);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2, "Error map\n", 10);
		exit(EXIT_FAILURE);
	} 
}