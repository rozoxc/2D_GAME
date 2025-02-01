/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:17 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/01 10:07:10 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (new_x < 0 || new_x >= game->map->width ||
        new_y < 0 || new_y >= game->map->height)
        return (0);

    char next_pos = game->map->grid[new_y][new_x];
    if (next_pos == '1')
        return (0);

    if (next_pos == 'C')
    {
        game->collectibles++;
        game->map->grid[new_y][new_x] = '0';
    }
    else if (next_pos == 'E')
    {
        if (game->collectibles == game->total_collectibles)
        {
            printf("You won in %d moves!\n", game->moves + 1);
            mlx_destroy_window(game->mlx, game->win);
        }
        return (0);
    }

    game->player_x = new_x;
    game->player_y = new_y;
    return (1);
}