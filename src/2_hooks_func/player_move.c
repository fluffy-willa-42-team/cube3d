/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/12/30 12:15:39 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>

#include "mlx_utils.h"
#include <stdio.h>

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);

t_bool	is_a_wall_move(t_game *game, t_coord_f64 inter_point)
{
	t_wall_inter	inter;

	inter = get_wall(game, inter_point);
	if (inter.text1 && !(inter.text1->type & NO_CLIP))
		return (TRUE);
	if (inter.text2 && !(inter.text2->type & NO_CLIP))
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Player can move if in the movement between p1 and p2 and they
 * encounter no walls or any pass through walls in the first intersection and if
 * p2 + R does not encounter any walls tha aren't pass through.
 *
 * R < 0.5 or 2R < 1
 * 
 * Speed <= 1
 */
void	player_move(t_game *game, t_coord_f64 player, t_coord_f64 incr)
{
	const t_coord_f64	inter_p1_p2 = set_f64(
			(int) player.x + (int []){0, 1}[incr.x > 0],
			(int) player.y + (int []){0, 1}[incr.y > 0]);
	const t_coord_f64	inter_p2_r = set_f64(
			(int)(player.x + incr.x) + (int []){0, 1}[incr.x > 0],
			(int)(player.y + incr.y) + (int []){0, 1}[incr.y > 0]);
	t_coord_f64			dest;

	dest = set_f64(player.x + incr.x, player.y + incr.y);
	if ((int) player.x != (int)(dest.x) && (int) player.y != (int)(dest.y))
		return ;
	if ((int) player.x != (int)(dest.x)
		&& is_a_wall_move(game, set_f64(inter_p1_p2.x, player.y)))
		dest.x = player.x;
	else if (fabs(inter_p2_r.x - dest.x) <= game->param.ray
		&& is_a_wall_move(game, set_f64(inter_p2_r.x, dest.y)))
		dest.x = player.x;
	if ((int) player.y != (int)(dest.y)
		&& is_a_wall_move(game, set_f64(player.x, inter_p1_p2.y)))
		dest.y = player.y;
	else if ((fabs(inter_p2_r.y - dest.y) <= game->param.ray)
		&& is_a_wall_move(game, set_f64(dest.x, inter_p2_r.y)))
		dest.y = player.y;
	game->player.pos = dest;
}
