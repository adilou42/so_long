/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:46:04 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 19:23:58 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_mlx_error(char **map)
{
	free_map(map);
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	print_error(t_map *lmap, int nb)
{
	ft_lstclear(&lmap);
	if (nb == 2)
	{
		write(1, "Error missing exit\n", 19);
		exit(EXIT_FAILURE);
	}
	else if (nb == 3)
	{
		write(1, "Error missing player\n", 21);
		exit(EXIT_FAILURE);
	}
	else if (nb == 4)
	{
		write(1, "Error missing collectible\n", 26);
		exit(EXIT_FAILURE);
	}
	else if (nb == 5)
	{
		write(1, "Error invalid file\n", 19);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}
