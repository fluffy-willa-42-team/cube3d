/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:32:41 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect	get_init_x(t_game *game, double alpha, double tan_a);
t_intersect	get_init_y(t_game *game, double alpha, double tan_a);
t_intersect	get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect	get_step_y(t_intersect prev, double alpha, double tan_a);

int	is_a_wall_vue(t_wall_inter inter)
{
	if (inter.text1 && !(inter.text1->type & TRANSPARENCY))
		return (1);
	if (inter.text2 && !(inter.text2->type & TRANSPARENCY))
		return (1);
	return (0);
}

t_inter	get_intersect(t_game *game, double alpha, double tan_a)
{
	t_intersect	x_inter;
	t_intersect	y_inter;
	double		x_dist;
	double		y_dist;

	x_inter = get_init_x(game, alpha, tan_a);
	y_inter = get_init_y(game, alpha, tan_a);
	x_dist = get_distance(game, x_inter.point);
	y_dist = get_distance(game, y_inter.point);
	while (1)
	{
		if (x_dist < y_dist)
		{
			if (is_a_wall_vue(get_wall(game, x_inter.point)))
				return ((t_inter){x_inter.point, x_inter, y_inter});
			x_inter = get_step_x(x_inter, alpha, tan_a);
			x_dist = get_distance(game, x_inter.point);
		}
		else
		{
			if (is_a_wall_vue(get_wall(game, y_inter.point)))
				return ((t_inter){y_inter.point, x_inter, y_inter});
			y_inter = get_step_y(y_inter, alpha, tan_a);
			y_dist = get_distance(game, y_inter.point);
		}
	}
}
