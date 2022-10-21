/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:16:26 by awillems          #+#    #+#             */
/*   Updated: 2022/10/21 18:30:34 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

mlx_image_t	*g_img;

double dist(t_coord a, t_coord b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

t_coord get_wall_coord(t_coord p, t_coord delta, int do_x, int do_y)
{
	return ((t_coord) {(int) (p.x - ((int []){0, 1}[delta.x < 0]) * do_x),
		(int) (p.y - ((int []){0, 1}[delta.y < 0]) * do_y)});
}

// Vertical   : 1 0
// Horizontal : 0 1
int is_a_wall(t_coord p, t_coord delta, int do_x, int do_y)
{
	t_coord res = get_wall_coord(p, delta, do_x, do_y);
	return (0 <= res.x && res.x < MAP_WIDTH && 0 <= res.y && res.y < MAP_HEIGHT
		&& map[(int) res.y][(int )res.x]);
}

void draw_ray(t_game *game)
{
	(void) game;

	// prectect for infinity
	if (0 <= game->p_dx && game->p_dx < 0.00001)
		game->p_dx = 0.00001;
	if (-0.00001 < game->p_dx && game->p_dx < 0)
		game->p_dx = -0.00001;
	if (0 <= game->p_dy && game->p_dy < 0.00001)
		game->p_dy = 0.00001;
	if (-0.00001 < game->p_dy && game->p_dy < 0)
		game->p_dy = -0.00001;
	double delta = game->p_dy / game->p_dx;

	t_coord pl = {game->p_x, game->p_y};
	t_coord deltas = {game->p_dx, game->p_dy};
	
	draw_line_coord(pl.x, pl.y, pl.x + game->p_dx, pl.y + game->p_dy, 0x0000ffff); 		// player view
	
	t_coord dv = find_init_vertical(game, delta);
	t_coord dh = find_init_horizontal(game, delta);
	
	double dist_v = dist(pl, dv);
	double dist_h = dist(pl, dh);

	int i = 0;

	while (!is_a_wall(dh, deltas, 0, 1) && !is_a_wall(dv, deltas, 1, 0) && i < 10)
	{
		if (dist_h < dist_v)
		{
			dh = find_step_horizontal(game, delta, dh);
			dist_v = dist(pl, dv);
		}
		else
		{
			dv = find_step_vertical(game, delta, dv);
			dist_h = dist(pl, dh);
		}
		i++;
	}
	if (is_a_wall(dh, deltas, 0, 1))
	{
		t_coord tmp = get_wall_coord(dh, deltas, 0, 1);
		draw_line_coord(pl.x, pl.y, dh.x, dh.y, 0x00FF00ff);
		draw_square(tmp.x * MINIMAP_SIZE, tmp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xFF0000FF);
	}
	else if (is_a_wall(dv, deltas, 1, 0))
	{
		t_coord tmp = get_wall_coord(dv, deltas, 1, 0);
		draw_line_coord(pl.x, pl.y, dv.x, dv.y, 0x00FF00ff);
		draw_square(tmp.x * MINIMAP_SIZE, tmp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xB523ABFF);
	}
	else
	{
		printf("Error\n");
	}

	// t_coord res = find_wall(game, delta, pl);
	// draw_line_coord(pl.x, pl.y, res.x, res.y, 0x00FFFFFFF);								// res of find wall
	// draw_square(res.x * MINIMAP_SIZE - 8, res.y * MINIMAP_SIZE - 8, 16, 0x00FFFFFFF);	// collision spot
	
	// dh = find_step_horizontal(game, delta, dh);
	// dh = find_step_horizontal(game, delta, dh);
	// if (is_a_wall(dh, deltas, 0, 1))
	// {
	// 	t_coord tmp = get_wall_coord(dh, deltas, 0, 1);
	// 	draw_line_coord(pl.x, pl.y, dh.x, dh.y, 0x00FF00ff);
	// 	draw_square(tmp.x * MINIMAP_SIZE, tmp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xFF0000FF);
	// }

	// dv = find_step_vertical(game, delta, dv);
	// dv = find_step_vertical(game, delta, dv);
	// if (is_a_wall(dv, deltas, 1, 0))
	// {
	// 	t_coord tmp = get_wall_coord(dv, deltas, 1, 0);
	// 	draw_line_coord(pl.x, pl.y, dv.x, dv.y, 0x00FF00ff);
	// 	draw_square(tmp.x * MINIMAP_SIZE, tmp.y * MINIMAP_SIZE, MINIMAP_SIZE, 0xB523ABFF);
	// }

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q))		{ game->p_a -= 0.001; if (game->p_a < 0)			game->p_a += 2 * PI;
		game->p_dx = cos(game->p_a);
		game->p_dy = sin(game->p_a);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))		{ game->p_a += 0.001; if (game->p_a > 2 * PI)		game->p_a -= 2 * PI;
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