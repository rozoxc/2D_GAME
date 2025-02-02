/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:21:13 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/01 21:36:09 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

#include "../includes/so_long.h"

static int check_map_char(char c, t_game *game, int i, int j)
{
    if (c == 'P')
    {
        game->player_count++;
        game->player_x = j;
        game->player_y = i;
        return (1);
    }
    else if (c == 'E')
    {
        game->exit_count++;
        return (1);
    }
    else if (c == 'C')
    {
        game->total_collectibles++;
        return (1);
    }
    else if (c == '0' || c == '1')
        return (1);
    return (0);
}

static int validate_map_chars(t_game *game)
{
    int i, j;

    game->player_count = 0;
    game->exit_count = 0;
    game->total_collectibles = 0;
    for (i = 0; i < game->map->height; i++)
    {
        for (j = 0; j < game->map->width; j++)
            if (!check_map_char(game->map->grid[i][j], game, i, j))
                return (0);
    }
    return (game->player_count == 1 && game->exit_count == 1 
        && game->total_collectibles > 0);
}

static int check_horizontal_walls(t_game *game)
{
    int i;

    for (i = 0; i < game->map->width; i++)
        if (game->map->grid[0][i] != '1' || 
            game->map->grid[game->map->height - 1][i] != '1')
            return (0);
    return (1);
}

static int check_vertical_walls(t_game *game)
{
    int i;

    for (i = 0; i < game->map->height; i++)
        if (game->map->grid[i][0] != '1' || 
            game->map->grid[i][game->map->width - 1] != '1')
            return (0);
    return (1);
}

static int validate_walls(t_game *game)
{
    return (check_horizontal_walls(game) && check_vertical_walls(game));
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

static int validate_line_length(char *line, int width)
{
    int len;

    len = ft_strlen(line);
    if (line[len - 1] == '\n')
        len--;
    return (len == width);
}

static int get_map_dimensions(char *filename, t_game *game)
{
    int fd;
    char *line;

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

static int alloc_grid_row(t_game *game, char *line, int i)
{
    game->map->grid[i] = malloc(sizeof(char) * (game->map->width + 1));
    if (!game->map->grid[i])
        return (0);
    ft_strlcpy(game->map->grid[i], line, game->map->width + 1);
    return (1);
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
    close(fd);
    return (1);
}

int parse_map(t_game *game, char *filename)
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
    if (!validate_walls(game) || !validate_map_chars(game))
    {
        free_grid(game->map->grid, game->map->height);
        free(game->map);
        return (0);
    }
    return (1);
}
