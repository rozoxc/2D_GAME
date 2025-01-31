/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:13 by ababdoul          #+#    #+#             */
/*   Updated: 2025/01/31 23:08:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int validate_map_chars(t_game *game)
{
    int i, j;
    int player = 0, exit = 0;
    game->total_collectibles = 0;

    for (i = 0; i < game->map->height; i++)
    {
        for (j = 0; j < game->map->width; j++)
        {
            char c = game->map->grid[i][j];
            if (c == 'P')
            {
                player++;
                game->player_x = j;
                game->player_y = i;
            }
            else if (c == 'E')
                exit++;
            else if (c == 'C')
                game->total_collectibles++;
            else if (c != '0' && c != '1')
                return (0);
        }
    }
    return (player == 1 && exit == 1 && game->total_collectibles > 0);
}

static int validate_walls(t_game *game)
{
    int i;

    for (i = 0; i < game->map->width; i++)
    {
        if (game->map->grid[0][i] != '1' || 
            game->map->grid[game->map->height - 1][i] != '1')
            return (0);
    }

    // Check left and right walls
    for (i = 0; i < game->map->height; i++)
    {
        if (game->map->grid[i][0] != '1' || 
            game->map->grid[i][game->map->width - 1] != '1')
            return (0);
    }
    return (1);
}

static void free_grid(char **grid, int height)
{
    int i;

    if (!grid)
        return;
    for (i = 0; i < height; i++)
    {
        if (grid[i])
            free(grid[i]);
    }
    free(grid);
}

static int get_map_dimensions(char *filename, t_game *game)
{
    int fd;
    char *line;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
        
    game->map->height = 0;
    game->map->width = 0;
    line = get_next_line(fd);
    if (line)
        game->map->width = ft_lenght(line) - 1;  // -1 for newline
    while (line)
    {
        if ((int)ft_lenght(line) - 1 != game->map->width && 
            ft_lenght(line) != game->map->width)  // Check last line without \n
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

static int allocate_and_fill_map(char *filename, t_game *game)
{
    int fd, i;
    char *line;

    game->map->grid = malloc(sizeof(char *) * game->map->height);
    if (!game->map->grid)
        return (0);

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free(game->map->grid);
        return (0);
    }

    i = 0;
    while (i < game->map->height)
    {
        line = get_next_line(fd);
        if (!line)
        {
            free_grid(game->map->grid, i);
            close(fd);
            return (0);
        }
        game->map->grid[i] = malloc(sizeof(char) * (game->map->width + 1));
        if (!game->map->grid[i])
        {
            free_grid(game->map->grid, i);
            free(line);
            close(fd);
            return (0);
        }
        ft_strlcpy(game->map->grid[i], line, game->map->width + 1);
        free(line);
        i++;
    }
    close(fd);
    return (1);
}

int parse_map(t_game *game, char *filename)
{
    // Allocate map structure
    game->map = malloc(sizeof(t_map));
    if (!game->map)
        return (0);

    // Get map dimensions
    if (!get_map_dimensions(filename, game))
    {
        free(game->map);
        return (0);
    }

    // Allocate and fill map grid
    if (!allocate_and_fill_map(filename, game))
    {
        free(game->map);
        return (0);
    }
    if (!validate_walls(game) || !validate_map_chars(game))
    {
        free_grid(game->map->grid, game->map->height);
        free(game->map);
        return (0);
    }
    return (1);
}
