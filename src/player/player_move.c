/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 13:31:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

double 	prot_tan(double alpha);

t_coord_f64 get_pos_x(t_game *game)
{
	return (set_f64(
		(int) game->player.coord.x,
		game->player.coord.y
	));
}

t_coord_f64 get_pos_y(t_game *game)
{
	return (set_f64(
		game->player.coord.x,
		(int) game->player.coord.y
	));
}

int				is_a_wall(t_wall_inter inter);
t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
t_intersect		get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr)
{
	if ((int) player.x == (int) (player.x + incr.x)
		|| !is_a_wall(get_wall(game, get_pos_x(game))))
		game->player.coord.x += incr.x;
	if ((int) player.y == (int) (player.y + incr.y)
		|| !is_a_wall(get_wall(game, get_pos_y(game))))
		game->player.coord.y += incr.y;

}