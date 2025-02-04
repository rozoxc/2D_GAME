/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:28 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/04 18:35:39 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_image(t_game	*game)
{
	int	widht;
	int	height;

	game->imgs.wall = mlx_xpm_file_to_image(game->mlx,
			"src/../assets/walls/11zon_so-long-wall.xpm", &widht, &height);
	game->imgs.player = mlx_xpm_file_to_image(game->mlx,
			"src/../assets/player/11zon_icons8-pixel-cat-40.xpm", &widht,
			&height);
	game->imgs.collectible = mlx_xpm_file_to_image(game->mlx,
			"src/../assets/coins/11zon_icons8-undertale-heart-30.xpm",
			&widht, &height);
	game->imgs.exit = mlx_xpm_file_to_image(game->mlx,
			"src/../assets/exit/house.xpm", &widht, &height);
	game->imgs.floor = mlx_xpm_file_to_image(game->mlx,
			"src/../assets/base.xpm", &widht, &height);
	if (!game->imgs.wall || !game->imgs.player || !game->imgs.collectible
		|| !game->imgs.exit || !game->imgs.floor)
		return (0);
	return (1);
}

void	render_tile(t_game *game, char tile, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.floor,
		screen_x, screen_y);
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

int	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			render_tile(game, game->map->grid[y][x], x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	return (0);
}
