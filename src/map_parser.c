/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:13 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/14 21:31:44 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	validate_walls(t_game *game)
{
	return (check_horizontal_walls(game) && check_vertical_walls(game));
}

int	fill_map_grid(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->map->height)
	{
		line = get_next_line(fd);
		if (!line || !alloc_grid_row(game, line, i))
		{
			free_grid(game->map->grid, i);
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		i++;
	}
	return (1);
}

int	allocate_and_fill_map(char *filename, t_game *game)
{
	int	fd;

	fd = open_map_file(filename, &game->map->grid, game->map->height);
	if (fd < 0 || !game->map->grid)
		return (0);
	if (!fill_map_grid(fd, game))
	{
		free_grid(game->map->grid, game->map->height);
		return (0);
	}
	close(fd);
	return (1);
}

int	parse_map(t_game *game, char *filename)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	if (!get_map_dimensions(filename, game))
	{
		free(game->map);
		return (0);
	}
	if (!allocate_and_fill_map(filename, game))
	{
		free(game->map);
		return (0);
	}
	if (!validate_walls(game) || !validate_map_chars(game)
		|| !validate_map_playability(game))
	{
		free_grid(game->map->grid, game->map->height);
		free(game->map);
		return (0);
	}
	return (1);
}
