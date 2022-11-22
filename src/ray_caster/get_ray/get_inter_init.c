/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:14:48 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 11:47:47 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_intersect	get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(player, set_f64(
		(double []){-delta.y, 1 - delta.y}[0 <= alpha && alpha < PI] / tan_a,
		(double []){-delta.y, 1 - delta.y}[0 <= alpha && alpha < PI]
	));
	res.nb_step = 1;
	return (res);
}

t_intersect	get_init_y(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(player, set_f64(
		(double []){1 - delta.x, -delta.x}[PI1_2 <= alpha && alpha < PI3_2],
		(double []){1 - delta.x, -delta.x}[PI1_2 <= alpha && alpha < PI3_2] * tan_a
	));
	res.nb_step = 1;
	return (res);
}
