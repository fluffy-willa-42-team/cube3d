/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:14:48 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 13:19:09 by awillems         ###   ########.fr       */
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
	res.wall = set_i32(res.point.x,
		(((float) res.point.y) - (int []){1, 0}[0 <= alpha && alpha < PI])
	);
	res.prev_wall = set_i32(
		res.wall.x,
		res.wall.y + (int []){1, -1}[0 <= alpha && alpha < PI]
	);
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
	res.wall = set_i32(
		(((float) res.point.x) - (int []){0, 1}[PI1_2 <= alpha && alpha < PI3_2]),
		((float) res.point.y)
	);
	res.prev_wall = set_i32(
		res.wall.x + (int []){-1, 1}[PI1_2 <= alpha && alpha < PI3_2],
		res.wall.y
	);
	res.nb_step = 1;
	return (res);
}



// t_intersect	get_init_x(t_coord_f64 player, t_inter *inter, double alpha, double tan_a)
// {
// 	t_intersect	res;

// 	res.point = inter->point;
// 	if (is_equal(inter->point.y, inter->wall.y))
// 	{
// 		if (0 <= alpha && alpha < PI)
// 		{
// 			res.wall = inter->wall;
// 			res.prev_wall = set_i32(inter->wall.x, inter->wall.y - 1);
// 		}
// 		else
// 		{
// 			res.wall = inter->wall;
// 			res.prev_wall = set_i32(inter->wall.x, inter->wall.y - 1);
// 		}
// 	}
// 	res.wall = set_i32(res.point.x,
// 		(((float) res.point.y) - (int []){1, 0}[0 <= alpha && alpha < PI])
// 	);
// 	res.prev_wall = set_i32(
// 		res.wall.x,
// 		res.wall.y + (int []){1, -1}[0 <= alpha && alpha < PI]
// 	);
// 	res.nb_step = inter->nb_step_x;
// 	return (res);
// }