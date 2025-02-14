/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:53:53 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/14 21:31:56 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_char(char c, t_game *game, int i, int j)
{
	if (i >= game->map->height || j >= game->map->width)
		return (0);
	if (c == 'P')
	{
		game->player_count++;
		game->player_x = j;
		game->player_y = i;
	}
	else if (c == 'E')
		game->exit_count++;
	else if (c == 'C')
		game->total_collectibles++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

int	validate_line_length(char *line, int width)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	return (len == width);
}

int	open_map_file(char *filename, char ***grid, int height)
{
	int	fd;

	*grid = malloc(sizeof(char *) * height);
	if (!*grid)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(*grid);
		return (-1);
	}
	return (fd);
}

int	check_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->width)
	{
		if (game->map->grid[0][i] != '1' ||
		game->map->grid[game->map->height - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->height)
	{
		if (game->map->grid[i][0] != '1' ||
			game->map->grid[i][game->map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
