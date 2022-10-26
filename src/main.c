/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/10/26 09:15:46 by awillems         ###   ########.fr       */
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

void angle_hook(t_game *game, double incrementation, int sign)
{
	game->player.alpha += incrementation;
	if (game->player.alpha < 0)
		game->player.alpha += sign * 2 * PI;
	game->player.dir.x = cos(game->player.alpha);
	game->player.dir.y = sin(game->player.alpha);
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_UP))
		pos_hook(&game->player.coord.y, -0.1, game->map.heigth);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_DOWN))
		pos_hook(&game->player.coord.y, 0.1, game->map.heigth);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_LEFT))
		pos_hook(&game->player.coord.x, -0.1, game->map.width);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_RIGHT))
		pos_hook(&game->player.coord.x, 0.1, game->map.width);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_A))
		angle_hook(game, -0.03, 1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_D))
		angle_hook(game, 0.03, -1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Q))
		angle_hook(game, -0.001, -1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_E))
		angle_hook(game, 0.001, 1);
	draw_minimap(game);
}

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	
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
		{{3.5f, 3.5f}, 0.0f, {cos(0), sin(0)}}
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
