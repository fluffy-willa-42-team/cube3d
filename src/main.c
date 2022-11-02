/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/11/02 15:09:54 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cube3d.h"
#include "ray_caster.h"
#include "MLX42/MLX42.h"

void pos2_hook(t_player *player, double incr_x, double incr_y, double size)
{
	player->coord.x += incr_x;
	if (player->coord.x < 0)
		player->coord.x += size;
	else if (player->coord.x > size)
		player->coord.x -= size;
	player->coord.y += incr_y;
	if (player->coord.y < 0)
		player->coord.y += size;
	else if (player->coord.y > size)
		player->coord.y -= size;
}

void angle_hook(t_game *game, double incrementation)
{
	game->player.alpha += incrementation;
	if (game->player.alpha < 0)
		game->player.alpha += PI2;
	else if (game->player.alpha > PI2)
		game->player.alpha -= PI2;
	game->player.delta.x = cos(game->player.alpha);
	game->player.delta.y = sin(game->player.alpha);
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_UP))
		pos2_hook(&game->player, 0.02 * game->player.delta.x, 0.02 * game->player.delta.y, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_DOWN))
		pos2_hook(&game->player, -0.02 * game->player.delta.x, -0.02 * game->player.delta.y, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_LEFT))
		pos2_hook(&game->player, 0.02 * game->player.delta.y, -0.02 * game->player.delta.x, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_RIGHT))
		pos2_hook(&game->player, -0.02 * game->player.delta.y, 0.02 * game->player.delta.x, game->map.height);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_A))
		angle_hook(game, -0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_D))
		angle_hook(game, 0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Q))
		angle_hook(game, -0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_E))
		angle_hook(game, 0.001);
	ray_caster(game);
	// draw_minimap(game);
}

int main(void)
{
	t_game game = {{NULL, NULL, WIN_HEIGHT, WIN_WIDTH},
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
		{{3.5f, 3.5f}, 0.0f, {cos(0), sin(0)}},
		{0, NULL, 0}
	};

	game.temp.type = IMAGE;
	game.temp.color = 0xFF00FFFF;
	game.temp.image = NULL;
	xpm_t *test = mlx_load_xpm42("../cool.xpm42");
	if (!test)
		return (EXIT_FAILURE);
	game.temp.image = &test->texture;

	game.param.mlx = mlx_init(game.param.width, game.param.height, "MLX42", true);
	if (!game.param.mlx)
		return (EXIT_FAILURE);

	game.param.img = mlx_new_image(game.param.mlx, game.param.width, game.param.height);
	if (!game.param.img)
		return (EXIT_FAILURE);
	mlx_loop_hook(game.param.mlx, &hook, &game);
	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop(game.param.mlx);

	mlx_delete_xpm42(test);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}
