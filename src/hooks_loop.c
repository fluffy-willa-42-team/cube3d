/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:47:01 by awillems          #+#    #+#             */
/*   Updated: 2022/12/12 16:47:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ray_caster.h"
#include "mlx_utils.h"
#include "key_macro.h"

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);
void	pos_hook(double incr_x, double incr_y, t_coord_f64 *move_vec);
void	speed_hook(t_game *game, double incrementation);
void	angle_hook(t_game *game, double incrementation);
void	scale_hook(t_game *game, double incrementation);
void	map_hook(t_game *game, int32_t incrementation);
void	map_point_hook(t_game *game, double incrementation);

// void	hook_loop(void *param)
// {
// 	t_game		*game;
// 	t_coord_f64	*cosin;
// 	t_coord_f64	move_vec;
// 	double		*speed;

// 	game = param;
// 	cosin = &game->player.cosin;
// 	move_vec = set_f64(0, 0);
// 	speed = &game->param.speed;
// 	if (mlx_is_key_down(game->param.mlx, KEY_ESCAPE))		mlx_destroy_window(game->param.mlx, game->param.win);;
// 	if (mlx_is_key_down(game->param.mlx, KEY_W))			pos_hook(*speed * cosin->x, *speed * cosin->y, &move_vec);
// 	if (mlx_is_key_down(game->param.mlx, KEY_S))			pos_hook(-*speed * cosin->x, -*speed * cosin->y, &move_vec);
// 	if (mlx_is_key_down(game->param.mlx, KEY_A))			pos_hook(*speed * cosin->y, -*speed * cosin->x, &move_vec);
// 	if (mlx_is_key_down(game->param.mlx, KEY_D))			pos_hook(-*speed * cosin->y, *speed * cosin->x, &move_vec);
// 	if (mlx_is_key_down(game->param.mlx, KEY_Q))			speed_hook(game, 0.01);
// 	if (mlx_is_key_down(game->param.mlx, KEY_E))			speed_hook(game, -0.01);
// 	if (mlx_is_key_down(game->param.mlx, KEY_Y))			scale_hook(game, 0.1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_H))			scale_hook(game, -0.1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_U))			scale_hook(game, 0.01);
// 	if (mlx_is_key_down(game->param.mlx, KEY_J))			scale_hook(game, -0.01);
// 	if (mlx_is_key_down(game->param.mlx, KEY_I))			map_point_hook(game, 0.1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_K))			map_point_hook(game, -0.1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_O))			map_hook(game, 1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_L))			map_hook(game, -1);
// 	if (mlx_is_key_down(game->param.mlx, KEY_NUM_4))		angle_hook(game, -0.05);
// 	if (mlx_is_key_down(game->param.mlx, KEY_NUM_6))		angle_hook(game, 0.05);
// 	if (mlx_is_key_down(game->param.mlx, KEY_NUM_1))		angle_hook(game, -0.01);
// 	if (mlx_is_key_down(game->param.mlx, KEY_NUM_3))		angle_hook(game, 0.01);
// 	if (move_vec.x != 0 || move_vec.y != 0)
// 		move_player(game, game->player.pos, move_vec);
// 	draw_rectangle(game, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT),
// 		0x000000ff);
// 	ray_caster(game);
// 	draw_minimap(game);
// }
