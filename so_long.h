/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:12:42 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 19:01:14 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include "GNL/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;
typedef struct coordonne
{
	int	x;
	int	y;
}	t_Coord;

typedef struct s_player
{
	int		dir;
	t_Coord	coord;
}	t_player;

typedef struct s_world
{
	char		**map;
	void		*wall;
	void		*floor;
	void		*perso;
	void		*collectible;
	void		*exit;
	int			height;
	int			width;
	int			item_count;
	int			move_count;
	t_player	*player;
	t_mlx		*mlx;
}	t_world;

typedef struct s_data
{
	int		count;
	t_world	img;
}	t_data;

typedef struct lst_map
{
	char			*line;
	size_t			len;
	struct lst_map	*next;
	char			**carte;
}	t_map;

char		*ft_strdup(const char *s);
int			lst_len(t_map *lmap);
void		ft_lstdelone(t_map *lst);
void		ft_lstclear(t_map **lst);
int			is_accessible(t_world *world, char c, int x, int y);
int			verif_map(char **map);
char		**initialize_tmap(t_map *lmap);
t_map		*creat_lmap_elem(char *line, size_t len);
int			push_last_elem(t_map **lmap, char *line, size_t len);
int			is_mapset(char c);
void		free_map(char **map);
void		print_mlx_error(char **map);
void		print_error(t_map *lmap, int nb);
void		display_map(t_world world);
t_map		*parsing_map(int fd, char *str);
int			exit_game(t_world *world);
int			is_exit(t_world world);
int			is_mapset(char c);
void		free_map(char **map);
void		free_world(t_world *world);
t_player	*create_player(int i, int j);
void		player_move(t_world *world, int dir, int y, int x);
void		move(t_world *world, int dir);
t_world		create_world(char **map, t_mlx *mlx);
int			verif_list(t_map *lmap);
void		display_elem(t_world world, int i, int j);
void		stock_images(t_world *world);
int			refresh(t_world *world);
int			deal_key(int key, t_world *world);
int			checkline(char *line);
int			checkcol(char **col, int j);
int			find_elem(char **map, char c);
int			check_wall(char **map, int height, int width);
int			check_rules(char **map, int height, int width);
int			is_item(char c);
int			map_height(char **map);
int			map_width(char **map);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		parsing_map_2(char **line, int fd, t_map *lmap);
void		hook(char **map, t_mlx mlx);

#endif
