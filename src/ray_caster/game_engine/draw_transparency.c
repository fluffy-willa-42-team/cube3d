/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:46:00 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:20:08 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect get_r_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_r_step_y(t_intersect prev, double alpha, double tan_a);

void		draw_wall_trans(t_game *game, uint32_t x, t_coord_f64 inter, double height);

void	draw_transparency(t_game *game, uint32_t x, t_inter inter, double alpha, double tan_a)
{
	double xDist = get_distance(game, inter.xInter.point);
	double yDist = get_distance(game, inter.yInter.point);

	while (inter.xInter.nb_step > 1 || inter.yInter.nb_step > 1)
	{
		if (xDist > yDist)
		{
			if (inter.xInter.nb_step <= 1)
			{
				xDist = -1;
				continue;
			}
			inter.xInter = get_r_step_x(inter.xInter, alpha, tan_a);
			xDist = get_distance(game, inter.xInter.point);
			draw_wall_trans(game, x, inter.xInter.point, xDist);
		}
		else
		{
			if (inter.yInter.nb_step <= 1)
			{
				yDist = -1;
				continue;
			}
			inter.yInter = get_r_step_y(inter.yInter, alpha, tan_a);
			yDist = get_distance(game, inter.yInter.point);
			draw_wall_trans(game, x, inter.yInter.point, yDist);
		}
	}
}