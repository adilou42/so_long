/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:17:11 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/03 21:04:02 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verif_list(t_map *lmap)
{
	t_map	*tmp;

	tmp = lmap;
	if (lst_len(lmap) < 3)
	{
		return (0);
	}
	while (tmp->next)
	{
		printf("len = %zu\n", tmp->len);
			printf("len->next = %zu\n", tmp->next->len);
		if (tmp->len != tmp->next->len || tmp->len < 4)
		{
			
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

t_map	*parsing_map(int fd)
{
	char	*line;
	t_map	*lmap;
	size_t	len;
	int		i;

	if (fd == -1)
		print_error(NULL);
	i = 0;
	len = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	lmap = creat_lmap_elem(line, len);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		push_last_elem(&lmap, line, ft_strlen(line));
	}
	if (!verif_list(lmap))
	{
		// write(1, "AA\n", 3);
		return (ft_lstclear(&lmap), NULL);
	}
	
	return (lmap);
}