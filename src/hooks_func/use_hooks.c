/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:06 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 14:45:37 by awillems         ###   ########.fr       */
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

void	change_speed(t_game *game)
{
	if (game->hooks.add_speed && game->hooks.reduce_speed)
		return ;
	if (game->hooks.add_speed)
		change_value_f(&game->param.speed, 0.05, 0.001, 10.001);
	else if (game->hooks.reduce_speed)
		change_value_f(&game->param.speed, -0.05, 0.001, 10.001);
	printf("=> %f\n", game->param.speed);
}

void	scale_map(t_game *game)
{
	if (game->hooks.map_scale_up && game->hooks.map_scale_down)
		return ;
	if (game->hooks.map_scale_up)
		change_value_f(&game->param.hob_mult, 0.05, 0.5, 100);
	else if (game->hooks.map_scale_down)
		change_value_f(&game->param.hob_mult, -0.05, 0.5, 100);
	printf("z => %f\n", game->param.hob_mult);
}

void	scale_minimap(t_game *game)
{
	if (game->hooks.minimap_scale_up && game->hooks.minimap_scale_down)
		return ;
	if (game->hooks.minimap_scale_up)
		change_value_i(&game->param.minimap_size, 1, 1, 100);
	else if (game->hooks.minimap_scale_down)
		change_value_i(&game->param.minimap_size, -1, 1, 100);
	printf("x => %u\n", game->param.minimap_size);
}

void	scale_player(t_game *game)
{
	if (game->hooks.player_scale_up && game->hooks.player_scale_down)
		return ;
	if (game->hooks.player_scale_up)
		change_value_f(&game->param.minimap_point_size, 1, 1, 100);
	else if (game->hooks.player_scale_down)
		change_value_f(&game->param.minimap_point_size, -1, 1, 100);
	printf("x => %f\n", game->param.minimap_point_size);
}

int	use_hooks(t_game *game)
{
	printf("Update Keys...\n");
	if (game->hooks.exit)
		exit_game(game);
	if (game->hooks.add_speed || game->hooks.reduce_speed)
		change_speed(game);
	// if (game->hooks.dir != 0)
	// 	move_player_new(game, game->hooks.dir)
	// if (game->hooks.look_left || game->hooks.look_right)
	// 	rotate_player(game);
	if (game->hooks.minimap_scale_up || game->hooks.minimap_scale_down)
		scale_minimap(game);
	if (game->hooks.player_scale_up || game->hooks.player_scale_down)
		scale_player(game);
	if (game->hooks.map_scale_up || game->hooks.map_scale_down)
		scale_map(game);
	return (1);
}
