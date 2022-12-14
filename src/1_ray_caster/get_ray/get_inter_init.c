/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:14:48 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:32:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_intersect	get_init_x(t_game *game, double alpha, double tan_a)
{
	const double	delta_y = game->player.pos.y - (int) game->player.pos.y;
	t_intersect		res;

	res.point = add_f64(game->player.pos, set_f64(
				(double []){-delta_y, 1 - delta_y}[0 <= alpha && alpha < PI]
				/ tan_a,
				(double []){-delta_y, 1 - delta_y}[0 <= alpha && alpha < PI]
				));
	res.nb_step = 1;
	return (res);
}

t_intersect	get_init_y(t_game *game, double alpha, double tan_a)
{
	const double	delta_x = game->player.pos.x - (int) game->player.pos.x;
	t_intersect		res;

	res.point = add_f64(game->player.pos, set_f64(
				(double []){1 - delta_x, -delta_x}
			[PI1_2 <= alpha && alpha < PI3_2],
				(double []){1 - delta_x, -delta_x}
			[PI1_2 <= alpha && alpha < PI3_2] * tan_a
				));
	res.nb_step = 1;
	return (res);
}
