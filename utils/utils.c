/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:38:46 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/14 21:32:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_file(char *file)
{
	int	len;

	if (file == NULL)
		return (0);
	len = ft_lenght(file);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") != 0)
		return (0);
	return (1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	if (map->grid)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	flood_fill(char **grid, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map->height || y >= game->map->width)
		return ;
	if (grid[x][y] == '1' || grid[x][y] == 'X')
		return ;
	if (grid[x][y] == 'C')
		game->collectibles++;
	if (grid[x][y] == 'E')
		game->game_won = 1;
	grid[x][y] = 'X';
	flood_fill(grid, x + 1, y, game);
	flood_fill(grid, x - 1, y, game);
	flood_fill(grid, x, y + 1, game);
	flood_fill(grid, x, y - 1, game);
}

int	validate_map_playability(t_game *game)
{
	char	**temp_grid;
	int		i;

	temp_grid = malloc(sizeof(char *) * game->map->height);
	if (!temp_grid)
		return (0);
	i = 0;
	while (i < game->map->height)
	{
		temp_grid[i] = ft_strdup(game->map->grid[i]);
		if (!temp_grid[i])
		{
			free_grid(temp_grid, i);
			return (0);
		}
		i++;
	}
	game->collectibles = 0;
	game->game_won = 0;
	flood_fill(temp_grid, game->player_y, game->player_x, game);
	free_grid(temp_grid, game->map->height);
	return (game->collectibles == game->total_collectibles && game->game_won);
}
