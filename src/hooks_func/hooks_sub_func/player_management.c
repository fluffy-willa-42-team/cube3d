/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:27:39 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 15:30:57 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

void	add_f64_ptr(t_coord_f64 *a, t_coord_f64 b);
void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);

void	change_value_f(double *v, double x, double y, double z);

void	move_player_hook(t_game *game, t_dir dir)
{
	t_coord_f64	*cosin;
	double		*speed;
	t_coord_f64	move_vec;

	cosin = &game->player.cosin;
	speed = &game->param.speed;
	move_vec = set_f64(0, 0);
	if (dir & FRONT && dir & BACK)
		dir &= ~(FRONT | BACK);
	if (dir & RIGHT && dir & LEFT)
		dir &= ~(RIGHT | LEFT);
	if (dir & FRONT)
		add_f64_ptr(&move_vec, set_f64(*speed * cosin->x, *speed * cosin->y));
	if (dir & BACK)
		add_f64_ptr(&move_vec, set_f64(*speed * -cosin->x, *speed * -cosin->y));
	if (dir & RIGHT)
		add_f64_ptr(&move_vec, set_f64(*speed * cosin->y, *speed * -cosin->x));
	if (dir & LEFT)
		add_f64_ptr(&move_vec, set_f64(*speed * -cosin->y, *speed * cosin->x));
	move_player(game, game->player.pos, move_vec);
}

void	rotate_player(t_game *game)
{
	if (game->hooks.look_left && game->hooks.look_right)
		return ;
	if (game->hooks.look_right)
		game->player.alpha += 0.05;
	else if (game->hooks.look_left)
		game->player.alpha -= 0.05;
	if (game->player.alpha < 0)
		game->player.alpha += PI2;
	else if (game->player.alpha > PI2)
		game->player.alpha -= PI2;
	game->player.cosin.x = cos(game->player.alpha);
	game->player.cosin.y = sin(game->player.alpha);
}

void	change_speed(t_game *game)
{
	if (game->hooks.add_speed && game->hooks.reduce_speed)
		return ;
	if (game->hooks.add_speed)
		change_value_f(&game->param.speed, 0.05, 0.001, 10.001);
	else if (game->hooks.reduce_speed)
		change_value_f(&game->param.speed, -0.05, 0.001, 10.001);
}
