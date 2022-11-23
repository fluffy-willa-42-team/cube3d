/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:48:14 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 13:17:29 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_intersect get_step_x(t_intersect prev, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(prev.point, set_f64(
		(double []){-1, 1}[0 <= alpha && alpha < PI] / tan_a,
		(double []){-1, 1}[0 <= alpha && alpha < PI]
	));
	res.nb_step = prev.nb_step + 1;
	return (res);
}

t_intersect get_step_y(t_intersect prev, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(prev.point, set_f64(
		(double []){1, -1}[PI1_2 <= alpha && alpha < PI3_2],
		(double []){1, -1}[PI1_2 <= alpha && alpha < PI3_2] * tan_a
	));
	res.nb_step = prev.nb_step + 1;
	return (res);
}

t_intersect get_r_step_x(t_intersect prev, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(prev.point, set_f64(
		(double []){1, -1}[0 <= alpha && alpha < PI] / tan_a,
		(double []){1, -1}[0 <= alpha && alpha < PI]
	));
	res.nb_step = prev.nb_step - 1;
	return (res);
}

t_intersect get_r_step_y(t_intersect prev, double alpha, double tan_a)
{
	t_intersect	res;

	res.point = add_f64(prev.point, set_f64(
		(double []){-1, 1}[PI1_2 <= alpha && alpha < PI3_2],
		(double []){-1, 1}[PI1_2 <= alpha && alpha < PI3_2] * tan_a
	));
	res.nb_step = prev.nb_step - 1;
	return (res);
}
