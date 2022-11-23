/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparency.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:46:00 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 13:23:23 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect get_r_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_r_step_y(t_intersect prev, double alpha, double tan_a);

void draw_point(t_game *game, t_coord_f64 pos, int size, uint32_t color);

void	draw_transparency(t_game *game, t_inter inter, double alpha, double tan_a)
{
	
	printf("%d %d\n", inter.xInter.nb_step, inter.yInter.nb_step);
	// inter.xInter = get_r_step_x(inter.xInter, alpha, tan_a);
	// inter.yInter = get_r_step_y(inter.yInter, alpha, tan_a);
	
	double xDist = get_distance(game, inter.xInter.point);
	double yDist = get_distance(game, inter.yInter.point);

	draw_point(game, inter.xInter.point, game->param.minimap_point_size, 0xff0000ff);
	draw_point(game, inter.yInter.point, game->param.minimap_point_size, 0x0000ffff);

	printf("%d %d\n", inter.xInter.nb_step, inter.yInter.nb_step);
	while (inter.xInter.nb_step > 1 || inter.yInter.nb_step > 1)
	{
		if (xDist > yDist && inter.xInter.nb_step > 1)
		{
			printf("xStep\n");
			// draw wall
			inter.xInter = get_r_step_x(inter.xInter, alpha, tan_a);
			draw_point(game, inter.xInter.point, game->param.minimap_point_size, 0xc46931ff);
			xDist = get_distance(game, inter.xInter.point);
		}
		else
		{
			printf("yStep\n");
			// draw wall
			inter.yInter = get_r_step_y(inter.yInter, alpha, tan_a);
			draw_point(game, inter.yInter.point, game->param.minimap_point_size, 0x3185c4ff);
			yDist = get_distance(game, inter.yInter.point);
		}
	}
}