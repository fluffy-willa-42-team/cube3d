/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:00:39 by awillems          #+#    #+#             */
/*   Updated: 2022/12/15 11:35:36 by awillems         ###   ########.fr       */
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

int	exit_cube3d(t_game *game);

void	update_win(t_game *game)
{
	// draw_rectangle(game, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), 0x00FFFFFF);
	ray_caster(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->param.mlx, game->param.win, game->param.img, 0, 0);
}

int	do_key(int keycode, t_game *game)
{
	t_coord_f64	*cosin;
	t_coord_f64	move_vec;
	double		*speed;

	cosin = &game->player.cosin;
	move_vec = set_f64(0, 0);
	speed = &game->param.speed;
	if (keycode == KEY_ESCAPE)			exit_cube3d(game);
	else if (keycode == KEY_W)			pos_hook(*speed * cosin->x, *speed * cosin->y, &move_vec);
	else if (keycode == KEY_S)			pos_hook(-*speed * cosin->x, -*speed * cosin->y, &move_vec);
	else if (keycode == KEY_A)			pos_hook(*speed * cosin->y, -*speed * cosin->x, &move_vec);
	else if (keycode == KEY_D)			pos_hook(-*speed * cosin->y, *speed * cosin->x, &move_vec);
	else if (keycode == KEY_Q)			speed_hook(game, 0.01);
	else if (keycode == KEY_E)			speed_hook(game, -0.01);
	else if (keycode == KEY_Y)			scale_hook(game, 0.1);
	else if (keycode == KEY_H)			scale_hook(game, -0.1);
	else if (keycode == KEY_U)			scale_hook(game, 0.01);
	else if (keycode == KEY_J)			scale_hook(game, -0.01);
	else if (keycode == KEY_I)			map_point_hook(game, 0.1);
	else if (keycode == KEY_K)			map_point_hook(game, -0.1);
	else if (keycode == KEY_O)			map_hook(game, 1);
	else if (keycode == KEY_L)			map_hook(game, -1);
	else if (keycode == KEY_NUM_4)		angle_hook(game, -0.05);
	else if (keycode == KEY_NUM_6)		angle_hook(game, 0.05);
	else if (keycode == KEY_NUM_1)		angle_hook(game, -0.01);
	else if (keycode == KEY_NUM_3)		angle_hook(game, 0.01);
	if (move_vec.x != 0 || move_vec.y != 0)
		move_player(game, game->player.pos, move_vec);
	update_win(game);
	return (0);
}