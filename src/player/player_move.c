/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/12/28 11:55:17 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>

#include "mlx_utils.h"

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);

int	is_a_wall_move(t_game *game, t_coord_f64 inter_point)
{
	t_wall_inter inter;

	inter = get_wall(game, inter_point);
	if (inter.text1 && !(inter.text1->type & ALLOW_CLIP))
		return (1);
	if (inter.text2 && !(inter.text2->type & ALLOW_CLIP))
		return (1);
	return (0);
}

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incr)
{
	if ((int) player.x == (int)(player.x + incr.x)
		|| !is_a_wall_move(game, set_f64((int) player.x + (int []){0, 1}[incr.x > 0], player.y)))
		game->player.pos.x += incr.x;
	if ((int) player.y == (int)(player.y + incr.y)
		|| !is_a_wall_move(game, set_f64(player.x, (int) player.y + (int []){0, 1}[incr.y > 0])))
		game->player.pos.y += incr.y;
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
	t_coord_f64 destination = set_f64(player.x + incr.x, player.y + incr.y);
	double		ray = game->param.ray;

	double	xinter_p1_p2 = (int) player.x + (int []){0, 1}[incr.x > 0];
	double	xinter_p2_r = (int) destination.x + (int []){0, 1}[incr.x > 0];
	if ((int) player.x != (int)(player.x + incr.x))
	{
		if (is_a_wall_move(game, set_f64(xinter_p1_p2, player.y)))
			destination.x = xinter_p1_p2 + (int []){ray, -ray}[incr.x > 0];
	}
	else if (fabs(xinter_p2_r - destination.x) <= ray
		&& is_a_wall_move(game, set_f64(xinter_p2_r, destination.y)))
		destination.x = xinter_p2_r + (int []){ray, -ray}[incr.x > 0];
		
	double	yinter_p1_p2 = (int) player.y + (int []){0, 1}[incr.y > 0];
	double	yinter_p2_r = (int) destination.y + (int []){0, 1}[incr.y > 0];
	if ((int) player.y != (int)(player.y + incr.y))
	{
		if (is_a_wall_move(game, set_f64(player.x, yinter_p1_p2)))
			destination.y = yinter_p1_p2 + (int []){ray, -ray}[incr.y > 0];
	}
	else if ((fabs(yinter_p2_r - destination.y) <= ray)
		&& is_a_wall_move(game, set_f64(destination.x, yinter_p2_r)))
		destination.y = yinter_p2_r + (int []){ray, -ray}[incr.y > 0];
	game->player.pos = destination;
}
