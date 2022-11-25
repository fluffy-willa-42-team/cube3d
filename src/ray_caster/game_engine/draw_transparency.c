/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:46:00 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 13:16:29 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect	get_r_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect	get_r_step_y(t_intersect prev, double alpha, double tan_a);

void		draw_wall_trans(t_game *game, uint32_t x, t_coord_f64 inter,
				double height);

void	draw_transparency(
	t_game *game,
	uint32_t x,
	t_inter inter,
	double alpha,
	double tan_a
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
			if (inter.x_inter.nb_step <= 1)
			{
				x_dist = -1;
				continue ;
			}
			inter.x_inter = get_r_step_x(inter.x_inter, alpha, tan_a);
			x_dist = get_distance(game, inter.x_inter.point);
			draw_wall_trans(game, x, inter.x_inter.point, x_dist);
		}
		else
		{
			if (inter.y_inter.nb_step <= 1)
			{
				y_dist = -1;
				continue ;
			}
			inter.y_inter = get_r_step_y(inter.y_inter, alpha, tan_a);
			y_dist = get_distance(game, inter.y_inter.point);
			draw_wall_trans(game, x, inter.y_inter.point, y_dist);
		}
	}
}