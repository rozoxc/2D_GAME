/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:49:57 by ababdoul          #+#    #+#            */
/*   Updated: 2025/02/01 15:09:23 by ababdoul         ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libs/minilibx_opengl_20191021/mlx.h"
# include "../utils/get_next_line.h"
# include <stdio.h>

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
    void    *wall;
    void    *player;
    void    *collectible;
    void    *exit;
    void    *floor;
}   t_images;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
}   t_map;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_map       *map;
    t_images    imgs;
    int         player_x;
    int         player_y;
    int         moves;
    int         collectibles;
    int         total_collectibles;
    int         player_count;
    int         exit_count;
    int         game_won;
}   t_game;

int     init_game(t_game *game);
void    clean_game(t_game *game);
int     parse_map(t_game *game, char *filename);
void    setup_hooks(t_game *game);

int     move_player(t_game *game, int dx, int dy);
int     render_game(t_game *game);
int    load_image(t_game *game);

int     handle_keypress(int keycode, t_game *game);
int     handle_close(t_game *game);

size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
int  ft_lenght(char *s);
int     ft_strcmp(char *s1, char *s2);

#endif