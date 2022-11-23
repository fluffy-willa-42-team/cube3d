/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:49:27 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 11:51:52 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cube3d.h"
#include "ray_caster.h"
#include "MLX42/MLX42.h"
#include "mlx_utils.h"

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);
void	pos_hook(double incr_x, double incr_y, t_coord_f64 *move_vec);
void	angle_hook(t_game *game, double incrementation);
void	scale_hook(t_game *game, double incrementation);
void	map_hook(t_game *game, int32_t incrementation);

void	hook(void *param)
{
	t_game		*game = param;
	t_coord_f64	*cosin = &game->player.cosin;
	t_coord_f64	move_vec = set_f64(0, 0);

	if (mlx_is_key_down(game->param.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->param.mlx);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_UP))
		pos_hook(0.02 * cosin->x, 0.02 * cosin->y, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_DOWN))
		pos_hook(-0.02 * cosin->x, -0.02 * cosin->y, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_LEFT))
		pos_hook(0.02 * cosin->y, -0.02 * cosin->x, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_RIGHT))
		pos_hook(-0.02 * cosin->y, 0.02 * cosin->x, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_KP_5))
		pos_hook(0.1 * cosin->x, 0.1 * cosin->y, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_KP_2))
		pos_hook(-0.1 * cosin->x, -0.1 * cosin->y, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_KP_1))
		pos_hook(0.1 * cosin->y, -0.1 * cosin->x, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_KP_3))
		pos_hook(-0.1 * cosin->y, 0.1 * cosin->x, &move_vec);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Y))
		scale_hook(game, 0.1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_H))
		scale_hook(game, -0.1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_U))
		scale_hook(game, 0.01);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_J))
		scale_hook(game, -0.01);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_I))
		scale_hook(game, 0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_K))
		scale_hook(game, -0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_O))
		map_hook(game, 1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_L))
		map_hook(game, -1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_A))
		angle_hook(game, -0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_D))
		angle_hook(game, 0.03);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_Q))
		angle_hook(game, -0.001);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_E))
		angle_hook(game, 0.001);
	if (move_vec.x != 0 || move_vec.y != 0)
		move_player(game, game->player.coord, move_vec);
	draw_minimap(game);
}

t_texture *init_image(t_texture *ptr, char *path);
t_texture *init_color(t_texture *ptr, uint32_t color);

t_texture *init_texture(t_texture *ptr, int type, char *path, uint32_t color);
void init_map(t_game *game);

int main(void)
{
	t_game game = {
		{NULL, NULL, 7, 32, WIN_HEIGHT, WIN_WIDTH},
		{{
			"ssssssssssssssssssss",
			"s_______   ________s",
			"s_______   ________s",
			"s_______   ________s",
			"s_______   ________s",
			"s_______   ________s",
			"s                  s",
			"s                  s",
			"s                  s",
			"s                  s",
			"sv                 s",
			"sv                 s",
			"sv   bv            s",
			"sv    vb           s",
			"sv    ahhhhhh      s",
			"sv           u     s",
			"s                  s",
			"s          cde     s",
			"s        f         s",
			"s                  s",
			"s      hhhhhu      s",
			"s   hhhhhhhhhhhh   s",
			"sssssssssssssssssass"
		}, NULL, 23, 20},
		{{15.5f, 15.5f}, ANGLE_START, {cos(ANGLE_START), sin(ANGLE_START)}},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, NULL, 0},
		{0, {0, 0}, NULL,			NULL,			NULL,			NULL,			&game.skybox,	&game.temp2},	// chunk0	' '
		{1, {0, 0}, &game.skybox,	&game.skybox,	&game.skybox,	&game.skybox,	NULL,			NULL},			// chunk1	's'
		{1, {0, 0}, NULL,			NULL,			&game.temp1,	&game.temp2,	&game.temp1,	&game.temp1},	// chunk2	'v'
		{1, {0, 0}, &game.temp1,	&game.temp1,	NULL,			NULL,			&game.temp1,	&game.temp1},	// chunk3	'h'
		{1, {0, 0}, NULL,			&game.temp1,	NULL,			&game.temp1,	&game.temp1,	&game.temp1},	// chunk4	'a'
		{1, {0, 0}, &game.temp,		&game.temp,		&game.temp,		&game.temp,		&game.temp,		&game.temp},	// chunk5	'b'
		{1, {0, 0}, &game.t_cont2,	&game.t_cont1,	NULL,			&game.t_cont4,	NULL,			NULL},			// cont1	'c'
		{1, {0, 0}, &game.t_cont3,	&game.t_cont3,	NULL,			NULL,			NULL,			NULL},			// cont2	'd'
		{1, {0, 0}, &game.t_cont1,	&game.t_cont2,	&game.t_cont5,	NULL,			NULL,			NULL},			// cont3	'e'
		{1, {0, 0}, &game.t_cont4,	&game.t_cont5,	&game.t_cont4,	&game.t_cont4,	NULL,			NULL},			// cont4	'f'
		{1, {0, 0}, &game.clip,		&game.clip,		&game.clip,		&game.clip,		&game.skybox,	&game.skybox},	// chunk6	'_'
		{1, {0, 0}, &game.temp3,	&game.temp3,	&game.temp3,	&game.temp3,	&game.skybox,	&game.skybox}	// chunk7	'u'
	};

	if (	!init_texture(&game.temp,		IMAGE | ALLOW_CLIP,		"./texture/mc/grass_side.xpm42",					0x0000FFFF)
		||	!init_texture(&game.temp1,		IMAGE,					"./texture/mc/stone.xpm42", 						0xFFFF00FF)
		||	!init_texture(&game.temp2,		IMAGE,					"./texture/mc/grass_top.xpm42", 					0x2596BEFF)
		||	!init_texture(&game.temp3,		IMAGE | TRANSPARENCY,	"./texture/bars.xpm42", 							0)
		||	!init_texture(&game.t_cont1,	IMAGE,					"./texture/cont/container_big_side_l.xpm42", 		0)
		||	!init_texture(&game.t_cont2,	IMAGE,					"./texture/cont/container_big_side_r.xpm42", 		0)
		||	!init_texture(&game.t_cont3,	IMAGE,					"./texture/cont/container_big_side_m.xpm42", 		0)
		||	!init_texture(&game.t_cont4,	IMAGE,					"./texture/cont/container_small_side.xpm42", 		0)
		||	!init_texture(&game.t_cont5,	IMAGE,					"./texture/cont/container_open.xpm42", 				0)
		||	!init_texture(&game.skybox,		IMAGE | SKYBOX,			"./texture/sky/skybox2.xpm42", 						0xf7d79aFF)
		)
		return (EXIT_FAILURE);
	game.clip.type |= TRANSPARENCY;

	game.map.map = malloc(sizeof(t_chunk) * game.map.width * game.map.height);
	if (!game.map.map)
		return (EXIT_FAILURE);
	init_map(&game);

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
	if (game.t_cont1.image)
		mlx_delete_texture(game.t_cont1.image);
	if (game.t_cont2.image)
		mlx_delete_texture(game.t_cont2.image);
	if (game.t_cont3.image)
		mlx_delete_texture(game.t_cont3.image);
	if (game.t_cont4.image)
		mlx_delete_texture(game.t_cont4.image);
	if (game.t_cont5.image)
		mlx_delete_texture(game.t_cont5.image);
	if (game.temp3.image)
		mlx_delete_texture(game.temp3.image);
	free(game.map.map);
	mlx_delete_image(game.param.mlx, game.param.img);
	mlx_terminate(game.param.mlx);
	return (EXIT_SUCCESS);
}

