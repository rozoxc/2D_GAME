/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:15:14 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/01 15:14:33 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
    void    *mlx;
    void    *win;
    void    *img;
    void    *background;
    int     win_width;
    int     win_height;
} t_vars;

int key_hook(int keycode, t_vars *vars)
{
    static int i = 1;
    printf("Move: %d\n", i++);
    return (0);
}

// Function to resize and set the background
void set_background(t_vars *vars, char *path)
{
    int     img_width;
    int     img_height;
    void    *original_img;
    char    *original_data;
    char    *background_data;
    int     original_bpp;
    int     original_line_length;
    int     original_endian;
    int     background_bpp;
    int     background_line_length;
    int     background_endian;
    int     x;
    int     y;

    // Load the original image
    original_img = mlx_xpm_file_to_image(vars->mlx, path, &img_width, &img_height);
    if (!original_img)
    {
        printf("Error: Cannot load the image at %s\n", path);
        exit(1);
    }

    // Get the original image data
    original_data = mlx_get_data_addr(original_img, &original_bpp, &original_line_length, &original_endian);

    // Create a new image for the background (same size as the window)
    vars->background = mlx_new_image(vars->mlx, vars->win_width, vars->win_height);
    background_data = mlx_get_data_addr(vars->background, &background_bpp, &background_line_length, &background_endian);

    // Copy and scale the original image to the background
    for (y = 0; y < vars->win_height; y++)
    {
        for (x = 0; x < vars->win_width; x++)
        {
            int src_x = x * img_width / vars->win_width;
            int src_y = y * img_height / vars->win_height;
            int src_offset = src_y * original_line_length + src_x * (original_bpp / 8);
            int dest_offset = y * background_line_length + x * (background_bpp / 8);

            *(unsigned int *)(background_data + dest_offset) = *(unsigned int *)(original_data + src_offset);
        }
    }

    // Clean up the original image
    mlx_destroy_image(vars->mlx, original_img);

    // Draw the background to the window
    mlx_put_image_to_window(vars->mlx, vars->win, vars->background, 0, 0);
}

int main(void)
{
    t_vars  vars;
    char    *path;

    vars.win_width = 640;
    vars.win_height = 480;
    path = "assets/base.xpm";
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "Pacman !!");

    // Set the background
    set_background(&vars, path);

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
