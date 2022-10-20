/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:16:26 by awillems          #+#    #+#             */
/*   Updated: 2022/10/20 17:54:05 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include <math.h>

#define PI 3.14159265359

#define WIDTH 600
#define HEIGHT 600

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 }
};

typedef struct s_game
{
	mlx_t	*mlx;
	
	float	p_x;
	float	p_y;
	float	p_a;
	float	p_dx;
	float	p_dy;
}	t_game;


mlx_image_t	*g_img;

#define MINIMAP_SIZE 64

void draw_square(float x, float y, int size, int32_t color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (x * size + i >= 0 && y * size + j >= 0 &&
				x * size + i < MAP_WIDTH * size && y * size + j < MAP_HEIGHT * size)
				mlx_put_pixel(g_img, x * size + i, y * size + j, color);
		}
	}
}

void draw_minimap(void)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (map[y][x] == 1)
				draw_square(x, y, MINIMAP_SIZE, 0xffff00ff);
			else
				draw_square(x, y, MINIMAP_SIZE, 0x222222ff);
		}
	}
}

void draw_line(double x1, double y1, double x2, double y2)
{
	float step;
	float dx = (x2 - x1);
	float dy = (y2 - y1);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	float x = x1;
	float y = y1;
	int i = 1;
	while (i <= step) {
		if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
			mlx_put_pixel(g_img, x, y, 0x00fffffff);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

void draw_image(t_game	*game)
{
	(void) game;
	draw_minimap();
	draw_square(game->p_x - 0.5, game->p_y - 0.5, MINIMAP_SIZE, 0xff0000ff);
	draw_line(game->p_x * MINIMAP_SIZE, game->p_y * MINIMAP_SIZE, (game->p_x + game->p_dx) * MINIMAP_SIZE, (game->p_y + game->p_dy) * MINIMAP_SIZE);
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) { mlx_close_window(game->mlx); }
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))		{ game->p_y -= 0.1; if (game->p_y < 0)			game->p_y += MAP_HEIGHT; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))	{ game->p_y += 0.1; if (game->p_y > MAP_HEIGHT)	game->p_y -= MAP_HEIGHT; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))	{ game->p_x -= 0.1; if (game->p_x < 0)			game->p_x += MAP_WIDTH;	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))	{ game->p_x += 0.1; if (game->p_x > MAP_WIDTH)	game->p_x -= MAP_WIDTH; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))		{ game->p_a -= PI/16; if (game->p_a < 0)			game->p_a += 2 * PI;
		game->p_dx = cos(game->p_a);
		game->p_dy = sin(game->p_a);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))		{ game->p_a += PI/16; if (game->p_a > 2 * PI)		game->p_a -= 2 * PI;
		game->p_dx = cos(game->p_a);
		game->p_dy = sin(game->p_a);
	}
	// printf("%f %f %f\n", game->p_a, game->p_dx, game->p_dy);
	draw_image(game);
}

int	main(void)
{
	t_game game;

	game.p_x = 2.5;
	game.p_y = 3.5;
	game.p_a = 0;
	game.p_dx = cos(game.p_a);
	game.p_dy = sin(game.p_a);
	
	game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!game.mlx)
		exit(EXIT_FAILURE);


	g_img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

	
	draw_image(&game);
	mlx_image_to_window(game.mlx, g_img, 0, 0);
	mlx_loop_hook(game.mlx, &hook, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}