/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:26:38 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/03 17:35:35 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
		i++;
	res = malloc((i + 1) * sizeof (char));
	if (!res)
		return (0);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	lst_len(t_map *lmap)
{
	t_map	*tmp;
	int		i;

	if (!lmap)
		return (0);
	tmp = lmap;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lstdelone(t_map *lst)
{
	if (!lst)
		return ;
	free(lst->line);
	free(lst);
}

void	ft_lstclear(t_map **lst)
{
	t_map	*t;
	t_map	*tmp;

	t = *lst;
	while (t)
	{
		tmp = t->next;
		ft_lstdelone(t);
		t = tmp;
	}
	*lst = NULL;
}

int	is_accessible(t_world *world, char c, int x, int y)
{
	if (c != '0' && c != 'C' && !(c == 'E' && world->item_count == 0))
		return (0);
	else if (c == 'E')
	{
		world->map[y][x] = 'F';
		return (0);
	}
	return (1);
}