/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:06 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 13:40:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ray_caster.h"
#include "mlx_utils.h"
#include "key_macro.h"
#include <stdio.h>

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr);
void	pos_hook(double incr_x, double incr_y, t_coord_f64 *move_vec);
void	speed_hook(t_game *game, double incrementation);
void	angle_hook(t_game *game, double incrementation);
void	scale_hook(t_game *game, double incrementation);
void	map_hook(t_game *game, int32_t incrementation);
void	map_point_hook(t_game *game, double incrementation);

int		exit_game(t_game *game);


void	change_speed(t_game *game)
{
	const double	incr = 0.05;

	if (game->hooks.add_speed && game->hooks.reduce_speed)
		return ;
	if (game->hooks.add_speed && game->param.speed + incr <= 10.001)
		game->param.speed += incr;
	else if (game->hooks.reduce_speed && game->param.speed - incr >= 0.001)
		game->param.speed -= incr;
	printf("=> %f\n", game->param.speed);
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
	// if (game->hooks.minimap_scale_up || game->hooks.minimap_scale_down
	// 	|| game->hooks.minimap_player_scale_up
	// 	|| game->hooks.minimap_player_scale_down)
	// 	scale_minimap(game);
	// if (game->hooks.map_scale_up || game->hooks.map_scale_down)
	// 	scale_map(game)
	return (1);
}
