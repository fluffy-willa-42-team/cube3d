/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/11/14 15:11:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cube3d.h"
#include "ray_caster.h"
#include "MLX42/MLX42.h"
#include "mlx_utils.h"

void pos2_hook(t_game *game, t_coord_f64 move_vec)
{
	t_player *player = &game->player;
	
	if (0 < player->coord.x + move_vec.x && player->coord.x + move_vec.x <= game->map.width)
		player->coord.x += move_vec.x;
	if (0 < player->coord.y + move_vec.y && player->coord.y + move_vec.y <= game->map.height)
		player->coord.y += move_vec.y;
}

void angle_hook(t_player *player, double incrementation)
{
	player->alpha += incrementation;
	if (player->alpha < 0)
		player->alpha += PI2;
	else if (player->alpha > PI2)
		player->alpha -= PI2;
	player->cosin = set_f64(
		cos(player->alpha),
		sin(player->alpha)
	);
	player->plane = set_f64(
		player->plane.x * player->cosin.x - player->plane.y * player->cosin.y,
		player->plane.y * player->cosin.y + player->plane.x * player->cosin.x
	);
}

void	hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_UP))
		pos2_hook(game, set_f64(0.05 * game->player.cosin.x, 0.05 * game->player.cosin.y));
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_DOWN))
		pos2_hook(game, set_f64(-0.05 * game->player.cosin.x, -0.05 * game->player.cosin.y));
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_LEFT))
		pos2_hook(game, set_f64(0.05 * game->player.cosin.y, -0.05 * game->player.cosin.x));
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_RIGHT))
		pos2_hook(game, set_f64(-0.05 * game->player.cosin.y, 0.05 * game->player.cosin.x));
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_W))
	{
		game->player.z += 0.02;
		if (game->player.z >= 1)
			game->player.z -= 1;
		double test = (double) (WIN_WIDTH - HEIGTH_OF_BLOCK) / WIN_HEIGHT * 2;
		printf("\n%f %f %f %f %f %f %f %f\n",
			test,
			(double) WIN_HEIGHT / WIN_WIDTH,
			(double) WIN_WIDTH / WIN_HEIGHT,
			(double) (WIN_WIDTH - HEIGTH_OF_BLOCK) / WIN_HEIGHT,
			(double) (WIN_HEIGHT - HEIGTH_OF_BLOCK) / WIN_WIDTH,
			(double) (WIN_WIDTH + HEIGTH_OF_BLOCK) / WIN_HEIGHT,
			(double) (WIN_HEIGHT + HEIGTH_OF_BLOCK) / WIN_WIDTH,
			(double) WIN_WIDTH / test
		);
		printf("res: %f %f %f %f\n\n", 
			(double) (HEIGTH_OF_BLOCK) / WIN_HEIGHT,
			(double) (HEIGTH_OF_BLOCK) / WIN_WIDTH,
			(double) (WIN_HEIGHT) / HEIGTH_OF_BLOCK,
			(double) (WIN_WIDTH) / HEIGTH_OF_BLOCK
		);
	}
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_S))
	{
		game->player.z -= 0.02;
		if (game->player.z <= 0)
			game->player.z += 1;
	}
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_A))
		angle_hook(&game->player, -0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_D))
		angle_hook(&game->player, 0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Q))
		angle_hook(&game->player, -0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_E))
		angle_hook(&game->player, 0.001);
	ray_caster(game);
	draw_minimap(game);
}

t_texture *init_image(t_texture *ptr, char *path);
t_texture *init_color(t_texture *ptr, uint32_t color);


int main(void)
{
	t_game game = {{NULL, NULL, WIN_HEIGHT, WIN_WIDTH},
		{{
			{1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 3, 0, 0, 0, 0, 0, 1},
			{1, 0, 2, 0, 1, 0, 1, 0, 1},
			{1, 0, 4, 3, 3, 0, 0, 0, 1},
			{1, 0, 2, 1, 1, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1},
		}, 8, 9},
		{{3.5f, 3.5f}, 0.5, 0.0f, {cos(0), sin(0)}, {0, 0.66}},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, {0, 0}, NULL, NULL, NULL, NULL, &game.temp2, &game.temp2},
		{1, {0, 0}, &game.temp, &game.temp, &game.temp, &game.temp, &game.temp1, &game.temp1},
		{1, {0, 0}, NULL, NULL, &game.temp1, &game.temp1, &game.temp1, &game.temp1},
		{1, {0, 0}, &game.temp1, &game.temp1, NULL, NULL, &game.temp1, &game.temp1},
		{1, {0, 0}, NULL, NULL, &game.temp1, NULL, &game.temp1, &game.temp1}
	};

	if (!init_image(&game.temp, "./texture/mc/grass_side.xpm42"))
		return (EXIT_FAILURE);
	// init_color(&game.temp, 0xFF00FFFF);

	if (!init_image(&game.temp1, "./texture/mc/stone.xpm42"))
		return (EXIT_FAILURE);
	// init_color(&game.temp1, 0xFF00FFFF);
	
	// if (!init_image(&game.skybox, "./texture/sky.xpm42"))
	// 	return (EXIT_FAILURE);
	init_color(&game.skybox, 0x000000FF);

	if (!init_image(&game.temp2, "./texture/mc/grass_top.xpm42"))
		return (EXIT_FAILURE);
	// init_color(&game.temp1, 0xFF00FFFF);

	game.param.mlx = mlx_init(game.param.width, game.param.height, "MLX42", true);
	if (!game.param.mlx)
		return (EXIT_FAILURE);

	game.param.img = mlx_new_image(game.param.mlx, game.param.width, game.param.height);
	if (!game.param.img)
		return (EXIT_FAILURE);
	mlx_image_to_window(game.param.mlx, game.param.img, 0, 0);
	mlx_loop_hook(game.param.mlx, &hook, &game);
	mlx_loop(game.param.mlx);

	if (game.temp.image)
		mlx_delete_texture(game.temp.image);
	if (game.temp1.image)
		mlx_delete_texture(game.temp1.image);
	if (game.temp2.image)
		mlx_delete_texture(game.temp2.image);
	if (game.skybox.image)
		mlx_delete_texture(game.skybox.image);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}
