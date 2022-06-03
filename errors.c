/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:46:04 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/03 19:09:29 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_mlx_error(char **map)
{
	free_map(map);
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	print_error(t_map *lmap)
{
	ft_lstclear(&lmap);
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

