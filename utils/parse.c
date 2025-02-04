/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:09:13 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/04 16:09:59 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	get_map_dimensions(char	*filename, t_game	*game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map->height = 0;
	line = get_next_line(fd);
	if (line)
		game->map->width = ft_strlen(line) - 1;
	while (line)
	{
		if (!validate_line_length(line, game->map->width))
		{
			free(line);
			close(fd);
			return (0);
		}
		game->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map->height > 0 && game->map->width > 0);
}

int	validate_map_chars(t_game *game)
{
	int	i;
	int	j;

	game->player_count = 0;
	game->exit_count = 0;
	game->total_collectibles = 0;
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (!check_map_char(game->map->grid[i][j], game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (game->player_count == 1 && game->exit_count == 1
		&& game->total_collectibles > 0);
}

void	free_grid(char	**grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

int	alloc_grid_row(t_game	*game, char	*line, int i)
{
	game->map->grid[i] = malloc(sizeof(char) * (game->map->width + 1));
	if (!game->map->grid[i])
		return (0);
	ft_strlcpy(game->map->grid[i], line, game->map->width + 1);
	return (1);
}
