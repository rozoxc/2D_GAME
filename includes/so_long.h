/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:49:57 by ababdoul          #+#    #+#            */
/*   Updated: 2025/02/04 15:53:14 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../utils/get_next_line.h"
# include "../printf/ft_printf.h"
# define TILE_SIZE 32
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124

typedef struct s_images
{
	void	*wall;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*floor;
}	t_images;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_images	imgs;
	int			player_x;
	int			player_y;
	int			moves;
	int			collectibles;
	int			total_collectibles;
	int			player_count;
	int			exit_count;
	int			game_won;
}	t_game;

int		init_game(t_game *game);
void	clean_game(t_game *game);
int		parse_map(t_game *game, char *filename);
void	setup_hooks(t_game *game);

int		move_player(t_game *game, int dx, int dy);
int		render_game(t_game *game);
int		load_image(t_game *game);

int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_lenght(char *s);
int		ft_strcmp(char *s1, char *s2);
int		check_file(char *file);
void	free_map(t_map *map);
int		get_map_dimensions(char *filename, t_game *game);
int		validate_map_chars(t_game *game);
int		allocate_and_fill_map(char *filename, t_game *game);
void	free_grid(char **grid, int height);
int		alloc_grid_row(t_game *game, char *line, int i);
int		check_map_char(char c, t_game *game, int i, int j);
int		fill_map_grid(int fd, t_game *game);
int		validate_line_length(char *line, int width);
int		open_map_file(char *filename, char ***grid, int height);
int		check_horizontal_walls(t_game *game);
int		check_vertical_walls(t_game *game);
#endif
