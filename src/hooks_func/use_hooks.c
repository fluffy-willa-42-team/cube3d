/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:06 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 15:20:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ray_caster.h"
#include "mlx_utils.h"
#include "key_macro.h"
#include <stdio.h>

int		exit_game(t_game *game);

void	change_value_i(uint32_t *v, uint32_t x, uint32_t y, uint32_t z);
void	change_value_f(double *v, double x, double y, double z);

void	update_win(t_game *game);

void	change_speed(t_game *game)
{
	if (game->hooks.add_speed && game->hooks.reduce_speed)
		return ;
	if (game->hooks.add_speed)
		change_value_f(&game->param.speed, 0.05, 0.001, 10.001);
	else if (game->hooks.reduce_speed)
		change_value_f(&game->param.speed, -0.05, 0.001, 10.001);
}

void	scale_map(t_game *game)
{
	if (game->hooks.map_scale_up && game->hooks.map_scale_down)
		return ;
	if (game->hooks.map_scale_up)
		change_value_f(&game->param.hob_mult, 0.05, 0.5, 100);
	else if (game->hooks.map_scale_down)
		change_value_f(&game->param.hob_mult, -0.05, 0.5, 100);
}

void	scale_minimap(t_game *game)
{
	if (game->hooks.minimap_scale_up && game->hooks.minimap_scale_down)
		return ;
	if (game->hooks.minimap_scale_up)
		change_value_i(&game->param.minimap_size, 1, 1,
			game->param.max_minimap_size);
	else if (game->hooks.minimap_scale_down)
		change_value_i(&game->param.minimap_size, -1, 1,
			game->param.max_minimap_size);
}

void	scale_player(t_game *game)
{
	if (game->hooks.player_scale_up && game->hooks.player_scale_down)
		return ;
	if (game->hooks.player_scale_up)
		change_value_f(&game->param.minimap_point_size, 1, 1, 100);
	else if (game->hooks.player_scale_down)
		change_value_f(&game->param.minimap_point_size, -1, 1, 100);
}

void	add_f64_ptr(t_coord_f64 *a, t_coord_f64 b);
void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);

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

int	use_hooks(t_game *game)
{
	printf("Update Keys...\n");
	if (game->hooks.exit)
		exit_game(game);
	if (game->hooks.add_speed || game->hooks.reduce_speed)
		change_speed(game);
	if (game->hooks.dir != 0)
		move_player_hook(game, game->hooks.dir);
	// if (game->hooks.look_left || game->hooks.look_right)
	// 	rotate_player(game);
	if (game->hooks.minimap_scale_up || game->hooks.minimap_scale_down)
		scale_minimap(game);
	if (game->hooks.player_scale_up || game->hooks.player_scale_down)
		scale_player(game);
	if (game->hooks.map_scale_up || game->hooks.map_scale_down)
		scale_map(game);
	update_win(game);
	return (1);
}
