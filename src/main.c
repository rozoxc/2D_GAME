/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:31 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/14 22:24:22 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map->width * 32,
			game->map->height * 32, "so_long");
	if (!game->win)
	{
		free(game->mlx);
		return (0);
	}
	game->moves = 0;
	game->collectibles = 0;
	return (1);
}

void	clean_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->map)
		free_map(game->map);
}

int	handle_errors(int ac, char *file)
{
	if (ac != 2)
	{
		ft_printf("Error\nInvalid number of arguments!\n");
		return (1);
	}
	if (!check_file(file))
	{
		ft_printf("Invalid extension !!\n");
		return (1);
	}
	return (0);
}

int	setup_game(t_game *game, char *file)
{
	if (!parse_map(game, file))
	{
		ft_printf("Error\nInvalid map!\n");
		return (0);
	}
	if (!init_game(game))
	{
		clean_game(game);
		return (0);
	}
	if (!load_image(game))
	{
		ft_printf("Can't load images !!!");
		clean_game(game);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (handle_errors(ac, av[1]))
		return (1);
	if (!setup_game(&game, av[1]))
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	clean_game(&game);
	return (0);
}
