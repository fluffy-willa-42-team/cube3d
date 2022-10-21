/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:07:21 by awillems          #+#    #+#             */
/*   Updated: 2022/10/21 16:16:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include <math.h>

#define PI 3.14159265359

#define WIDTH 600
#define HEIGHT 1000

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

#define MINIMAP_SIZE 64

typedef struct s_game
{
	mlx_t	*mlx;
	
	double	p_x;
	double	p_y;
	double	p_a;
	double	p_dx;
	double	p_dy;
}	t_game;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

extern mlx_image_t	*g_img;

static int map[MAP_HEIGHT][MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 }
};


void draw_line(double x1, double y1, double x2, double y2, int32_t color);
void draw_minimap(void);
void draw_square(float x, float y, int size, int32_t color);
void draw_line_coord(double x1, double y1, double x2, double y2, int32_t color);

t_coord find_init_vertical(t_game *game, double delta);
t_coord find_step_vertical(t_game *game, double delta, t_coord prev);
t_coord find_init_horizontal(t_game *game, double delta);
t_coord find_step_horizontal(t_game *game, double delta, t_coord prev);

/* ************************************************************************** */

#endif