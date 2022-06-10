/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:17:11 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/10 16:57:23 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verif_list(t_map *lmap)
{
	t_map	*tmp;

	tmp = lmap;
	if (lst_len(lmap) < 3)
		return (0);
	while (tmp->next)
	{
		if (tmp->len != tmp->next->len || tmp->len < 4)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_map	*parsing_map(int fd, char *str)
{
	char	*line;
	t_map	*lmap;
	size_t	len;
	int		i;

	if (ft_strncmp(str, ".ber", 4) == 0)
		print_error(NULL, 5);
	if (fd == -1)
		print_error(NULL, 0);
	i = 0;
	len = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	lmap = creat_lmap_elem(line, len);
	parsing_map_2(&line, fd, lmap);
	if (!verif_list(lmap))
		return (ft_lstclear(&lmap), NULL);
	return (lmap);
}

void	parsing_map_2(char **line, int fd, t_map *lmap)
{
	while (*line)
	{
		*line = get_next_line(fd);
		if (!(*line))
			break ;
		push_last_elem(&lmap, (*line), ft_strlen(*line));
	}
}
