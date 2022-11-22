/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 16:01:35 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>

#include "mlx_utils.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

double 	prot_tan(double alpha);

t_coord_f64 get_pos_x(t_coord_f64 pos, double incre)
{
	return (set_f64(
		(int) pos.x + (int []){0, 1}[incre > 0],
		pos.y
	));
}

t_coord_f64 get_pos_y(t_coord_f64 pos, double incre)
{
	return (set_f64(
		pos.x,
		(int) pos.y + (int []){0, 1}[incre > 0]
	));
}

int				is_a_wall(t_wall_inter inter);
t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
t_intersect		get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incre)
{

	t_wall_inter xWall = get_wall(game, get_pos_x(player, incre.x));
	t_wall_inter yWall = get_wall(game, get_pos_y(player, incre.y));

	if ((int) player.x == (int) (player.x + incre.x)
		|| !is_a_wall(xWall))
		game->player.coord.x += incre.x;
	if ((int) player.y == (int) (player.y + incre.y)
		|| !is_a_wall(yWall))
		game->player.coord.y += incre.y;

}