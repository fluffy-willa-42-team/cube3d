/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:46:00 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:05:42 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect	get_r_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect	get_r_step_y(t_intersect prev, double alpha, double tan_a);

void		draw_wall_trans(t_game *game, uint32_t x, t_coord_f64 inter,
				double height);

t_bool	draw_next_transparancy(
	t_game *game,
	t_intersect *inter,
	double *dist,
	t_draw_trans a
)
{
	if (inter->nb_step <= 1)
	{
		*dist = -1;
		return (TRUE);
	}
	*inter = a.func(*inter, a.alpha, a.tan_a);
	*dist = get_distance(game, inter->point);
	draw_wall_trans(game, a.x, inter->point, *dist);
	return (FALSE);
}

void	draw_transparency(
	t_game *game,
	uint32_t x,
	t_inter inter,
	t_ang_param a
)
{
	double	x_dist;
	double	y_dist;

	x_dist = get_distance(game, inter.x_inter.point);
	y_dist = get_distance(game, inter.y_inter.point);
	while (inter.x_inter.nb_step > 1 || inter.y_inter.nb_step > 1)
	{
		if (x_dist > y_dist)
		{
			draw_next_transparancy(game, &inter.x_inter, &x_dist,
				(t_draw_trans){a.alpha, a.tan_a, x, get_r_step_x});
		}
		else
		{
			draw_next_transparancy(game, &inter.y_inter, &y_dist,
				(t_draw_trans){a.alpha, a.tan_a, x, get_r_step_y});
		}
	}
}
