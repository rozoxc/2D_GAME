/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:39:31 by ababdoul          #+#    #+#             */
/*   Updated: 2025/01/31 22:58:53 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


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
static void free_map(t_map *map)
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
