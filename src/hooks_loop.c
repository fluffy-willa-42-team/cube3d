/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:47:01 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:55:45 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ray_caster.h"
#include "mlx_utils.h"

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);
void	pos_hook(double incr_x, double incr_y, t_coord_f64 *move_vec);
void	angle_hook(t_game *game, double incrementation);
void	scale_hook(t_game *game, double incrementation);
void	map_hook(t_game *game, int32_t incrementation);
void	map_point_hook(t_game *game, double incrementation);

void	hook_loop(void *param)
{
	t_game		*game;
	t_coord_f64	*cosin;
	t_coord_f64	move_vec;

	game = param;
	cosin = &game->player.cosin;
	move_vec = set_f64(0, 0);
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
		map_point_hook(game, 0.1);
	if (mlx_is_key_down(game->param.mlx, MLX_KEY_K))
		map_point_hook(game, -0.1);
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
		move_player(game, game->player.pos, move_vec);
	draw_rectangle(game, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT),
		0x000000ff);
	ray_caster(game);
	draw_minimap(game);
}
