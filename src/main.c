/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:16:26 by awillems          #+#    #+#             */
/*   Updated: 2022/10/21 15:09:29 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include <math.h>

#define PI 3.14159265359

#define WIDTH 1000
#define HEIGHT 1000

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


mlx_image_t	*g_img;

#define MINIMAP_SIZE 64

void draw_square(float x, float y, int size, int32_t color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (0 <= x && x + i < WIDTH && 0 <= y && y + j < HEIGHT)
				mlx_put_pixel(g_img, x + i, y + j, color);
		}
	}
}

void draw_minimap(void)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			draw_square(x * MINIMAP_SIZE, y * MINIMAP_SIZE, MINIMAP_SIZE, 0x111111ff);
			if (map[y][x] == 1)
				draw_square(x * MINIMAP_SIZE + 2, y * MINIMAP_SIZE + 2, MINIMAP_SIZE - 4, 0xffff22ff);
			else
				draw_square(x * MINIMAP_SIZE + 2, y * MINIMAP_SIZE + 2, MINIMAP_SIZE - 4, 0x333333ff);
		}
	}
}

void draw_line(double x1, double y1, double x2, double y2, int32_t color)
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
			mlx_put_pixel(g_img, x, y, color);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

void draw_line_coord(double x1, double y1, double x2, double y2, int32_t color)
{
	draw_line(x1 * MINIMAP_SIZE, y1 * MINIMAP_SIZE, x2 * MINIMAP_SIZE, y2 * MINIMAP_SIZE, color);
}

t_coord find_init_vertical(t_game *game, double delta)
{
	t_coord res;
	
	res.x = (int) game->p_x;
	if (game->p_dx > 0)
		res.x++;

	res.y = delta * (res.x - game->p_x) + game->p_y;
	return (res);
}

t_coord find_step_vertical(t_game *game, double delta, t_coord prev)
{
	t_coord res;

	res.x = prev.x + (int []){1, -1}[game->p_dx > 0];
	res.y = delta * (res.x - game->p_x) + game->p_y;
	return (res);
}

t_coord find_init_horizontal(t_game *game, double delta)
{
	t_coord res;
	
	res.y = (int) game->p_y;
	if (game->p_dy > 0)
		res.y++;

	res.x = (1 / delta) * (res.y - game->p_y) + game->p_x;
	return (res);
}

t_coord find_step_horizontal(t_game *game, double delta, t_coord prev)
{
	t_coord res;

	res.y = prev.y + (int []){-1, 1}[game->p_dy > 0];
	res.x = (1 / delta) * (res.y - game->p_y) + game->p_x;
	return (res);
}

double dist(t_coord a, t_coord b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

int is_a_wall(int x, int y)
{
	return (0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT && map[y][x]);
}


t_coord find_wall(t_game *game, double delta, t_coord pl)
{
	t_coord dh = find_init_horizontal(game, delta);
	t_coord dv = find_init_vertical(game, delta);

	float dist_v = dist(pl, dv);
	float dist_h = dist(pl, dh);
		if (dist_v < dist_h)
		{
			if (is_a_wall(dv.x + game->p_dx, dv.y))
				return (dv);
			else
			{
				dv = find_step_vertical(game, delta, dv);
				dist_v = dist(pl, dv);
			}
		}
		else
		{
			if (is_a_wall(dv.x + game->p_dx, dv.y))
				return (dh);
			else
			{
				dh = find_step_horizontal(game, delta, dh);
				dist_v = dist(pl, dh);
			}
	}
	return (dh);
}

void draw_ray(t_game *game)
{
	(void) game;

	if (0 <= game->p_dx && game->p_dx < 0.00001)
		game->p_dx = 0.00001;
	if (-0.00001 < game->p_dx && game->p_dx < 0)
		game->p_dx = -0.00001;
	if (0 <= game->p_dy && game->p_dy < 0.00001)
		game->p_dy = 0.00001;
	if (-0.00001 < game->p_dy && game->p_dy < 0)
		game->p_dy = -0.00001;
	double delta = game->p_dy / game->p_dx;

	
	// t_coord dh = find_init_horizontal(game, delta);
	// t_coord dv = find_init_vertical(game, delta);
	t_coord pl = {game->p_x, game->p_y};
	
	t_coord res = find_wall(game, delta, pl);
	draw_line_coord(pl.x, pl.y, pl.x + game->p_dx, pl.y + game->p_dy, 0x0000ffff);
	draw_line_coord(pl.x, pl.y, res.x, res.y, 0x330066ff);

	// t_coord temp;
	// temp.x = (int) dh.x;
	// temp.y = (int) (dh.y + game->p_dy);
	// if (0 <= temp.x && temp.x < MAP_WIDTH && 0 <= temp.y && temp.y < MAP_HEIGHT && map[(int) temp.y][(int) temp.x])
	// 	draw_square(temp.x * MINIMAP_SIZE, temp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xFF0000FF);
	// draw_line_coord(pl.x, pl.y, dh.x, dh.y, 0x00ff00ff);

	// temp.x = (int) (dv.x + game->p_dx);
	// temp.y = (int) dv.y;
	// if (0 <= temp.x && temp.x < MAP_WIDTH && 0 <= temp.y && temp.y < MAP_HEIGHT && map[(int) temp.y][(int) temp.x])
	// 	draw_square(temp.x * MINIMAP_SIZE, temp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xFF0000FF);
	// draw_line_coord(pl.x, pl.y, dv.x, dv.y, 0x0000ffff);

}

void draw_image(t_game	*game)
{
	draw_minimap();
	draw_square((game->p_x - 0.5) * MINIMAP_SIZE + 16, (game->p_y - 0.5) * MINIMAP_SIZE + 16, MINIMAP_SIZE - 32, 0xff2222ff);
	draw_ray(game);
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) { mlx_close_window(game->mlx); }
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))		{ game->p_y -= 0.1; if (game->p_y < 0)			game->p_y += MAP_HEIGHT; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))	{ game->p_y += 0.1; if (game->p_y > MAP_HEIGHT)	game->p_y -= MAP_HEIGHT; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))	{ game->p_x -= 0.1; if (game->p_x < 0)			game->p_x += MAP_WIDTH;	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))	{ game->p_x += 0.1; if (game->p_x > MAP_WIDTH)	game->p_x -= MAP_WIDTH; }
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))		{ game->p_a -= 0.03; if (game->p_a < 0)			game->p_a += 2 * PI;
		game->p_dx = cos(game->p_a);
		game->p_dy = sin(game->p_a);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))		{ game->p_a += 0.03; if (game->p_a > 2 * PI)		game->p_a -= 2 * PI;
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
	game.p_y = 5.5;
	game.p_a = 3*PI/2;
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
	mlx_delete_image(game.mlx, g_img);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}