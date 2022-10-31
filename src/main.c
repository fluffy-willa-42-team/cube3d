/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/10/28 09:28:21 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cube3d.h"
#include "ray_caster.h"
#include "MLX42/MLX42.h"

void pos_hook(double *coord, double incrementation, double size)
{
	*coord += incrementation;
	if (*coord < 0)
		*coord += size;
	else if (*coord > size)
		*coord -= size;
}

void angle_hook(t_game *game, double incrementation)
{
	game->player.alpha += incrementation;
	if (game->player.alpha < 0)
		game->player.alpha += PI2;
	else if (game->player.alpha > PI2)
		game->player.alpha -= PI2;
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_UP))
		pos_hook(&game->player.coord.y, -0.02, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_DOWN))
		pos_hook(&game->player.coord.y, 0.02, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_LEFT))
		pos_hook(&game->player.coord.x, -0.02, game->map.width);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_RIGHT))
		pos_hook(&game->player.coord.x, 0.02, game->map.width);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_A))
		angle_hook(game, -0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_D))
		angle_hook(game, 0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Q))
		angle_hook(game, -0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_E))
		angle_hook(game, 0.001);
	draw_minimap(game);
}

int main(void)
{
	t_game game = {{NULL, NULL, WIN_WIDTH, WIN_HEIGHT},
		{{
			{1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 1, 0, 0, 0, 0, 1},
			{1, 0, 1, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1},
		}, 8, 8},
		{{3.5f, 3.5f}, 0.0f}
	};
	

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
