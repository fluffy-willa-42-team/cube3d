/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 13:08:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "cube3d.h"
#include "ray_caster.h"
#include "MLX42/MLX42.h"

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_UP))		{ game->p_y -= 0.1; if (game->p_y < 0)			game->p_y += MAP_HEIGHT; }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))	{ game->p_y += 0.1; if (game->p_y > MAP_HEIGHT)	game->p_y -= MAP_HEIGHT; }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))	{ game->p_x -= 0.1; if (game->p_x < 0)			game->p_x += MAP_WIDTH;	}
	// if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))	{ game->p_x += 0.1; if (game->p_x > MAP_WIDTH)	game->p_x -= MAP_WIDTH; }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))		{ game->p_a -= 0.03; if (game->p_a < 0)			game->p_a += 2 * PI;
	// 	game->p_dx = cos(game->p_a);
	// 	game->p_dy = sin(game->p_a);
	// }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))		{ game->p_a += 0.03; if (game->p_a > 2 * PI)		game->p_a -= 2 * PI;
	// 	game->p_dx = cos(game->p_a);
	// 	game->p_dy = sin(game->p_a);
	// }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_Q))		{ game->p_a -= 0.001; if (game->p_a < 0)			game->p_a += 2 * PI;
	// 	game->p_dx = cos(game->p_a);
	// 	game->p_dy = sin(game->p_a);
	// }
	// if (mlx_is_key_down(game->mlx, MLX_KEY_E))		{ game->p_a += 0.001; if (game->p_a > 2 * PI)		game->p_a -= 2 * PI;
	// 	game->p_dx = cos(game->p_a);
	// 	game->p_dy = sin(game->p_a);
	// }
	// printf("%f %f %f\n", game->p_a, game->p_dx, game->p_dy);
	// draw_image(game);
}

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	
	t_game game = {{NULL, NULL, 500, 500}, {{
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	}, 8, 8}};

	game.param.mlx = mlx_init(game.param.width, game.param.height, "MLX42", true);
	
	game.param.img = mlx_new_image(game.param.mlx, game.param.width, game.param.height);

	draw_minimap(&game);
	
	mlx_loop_hook(game.param.mlx, &hook, &game);

	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop(game.param.mlx);

	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}
