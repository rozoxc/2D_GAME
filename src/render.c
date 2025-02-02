/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/02 10:30:28 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int    load_image(t_game *game)
{
    int widht;
    int height;
    
    widht = 15;
    height = 15;
    game->imgs.wall =  mlx_xpm_file_to_image(game->mlx, "src/../assets/walls/11zon_so-long-wall.xpm", &widht, &height);  
    game->imgs.player = mlx_xpm_file_to_image(game->mlx, "src/../assets/player/11zon_pacman-svgrepo-com.xpm", &widht, &height);
    game->imgs.collectible = mlx_xpm_file_to_image(game->mlx, "src/../assets/coins/11zon_so-long-coin.xpm", &widht, &height);
    game->imgs.exit = mlx_xpm_file_to_image(game->mlx, "src/../assets/exit/11zon_so-long-exit.xpm", &widht, &height);
    game->imgs.floor = mlx_xpm_file_to_image(game->mlx, "src/../assets/base.xpm", &widht, &height);
	if (!game->imgs.wall || !game->imgs.player || !game->imgs.collectible 
        || !game->imgs.exit || !game->imgs.floor)
        return (0);
    return (1);
}

int    render_game(t_game *game)
{
    int x, y;

    for (y = 0; y < game->map->height; y++)
    {
        for (x = 0; x < game->map->width; x++)
        {
            int screen_x = x * TILE_SIZE;
            int screen_y = y * TILE_SIZE;
            mlx_put_image_to_window(game->mlx, game->win, game->imgs.floor, 
                                   screen_x, screen_y);
            char tile = game->map->grid[y][x];
            if (tile == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->imgs.wall, 
                                       screen_x, screen_y);
            else if (tile == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->imgs.collectible, 
                                       screen_x, screen_y);
            else if (tile == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->imgs.exit, 
                                       screen_x, screen_y);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->imgs.player, 
                           game->player_x * TILE_SIZE, 
                           game->player_y * TILE_SIZE);
    return (0);
}
