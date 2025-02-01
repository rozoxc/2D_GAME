/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:31 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/01 12:17:08 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int check_file(char *file)
{
    int				len;

	len = ft_lenght(file);
	if (file == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") != 0)
		return (0);
	return (1);
}
int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->win = mlx_new_window(game->mlx, game->map->width * 32, game->map->height * 32 , "3acha lmalik");
    if (!game->win)
    {
        free(game->mlx);
        return (0);
    }
    game->moves = 0;
    game->collectibles = 0;
    return (1);
}
void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->grid)
    {
        for (i = 0; i < map->height; i++)
        {
            if (map->grid[i])
                free(map->grid[i]);
        }
        free(map->grid);
    }
    free(map);
}

void clean_game(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        free(game->mlx);
    if (game->map)
        free_map(game->map);
}

int main(int ac, char **av)
{
    t_game game;

    if (ac != 2)
    {
        printf("invalid argument !!!");
        return (1);
    }
    if (check_file(av[1]) == 0)
    {
        printf("invlaid file !!\n");
        return (1);
    }
    if (parse_map(&game , av[1]) == 0)
    {
        printf("invalid map !!\n");
        return (1);
    }
    if (init_game(&game))
    {
        clean_game(&game);
        return (1);
    }
    setup_hooks(&game);
    mlx_loop(game.mlx);
    clean_game(&game);
    return (0);
}
