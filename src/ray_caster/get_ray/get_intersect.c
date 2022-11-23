/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 12:07:29 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>
#include <stdio.h>

#include "mlx_utils.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

t_intersect	get_init_x(t_game *game, double alpha, double tan_a);
t_intersect	get_init_y(t_game *game, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);

double dist(t_coord_f64 a, t_coord_f64 b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}

double get_distance2(t_game *game, t_coord_f64 pos)
{
	return ((pos.x - game->player.coord.x) * game->player.cosin.x
		+ (pos.y - game->player.coord.y) * game->player.cosin.y);
}


t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
void			draw_rectangle_s(t_game *game, t_coord_f64 pos, uint32_t color);
double			get_distance(t_game *game, t_inter *inter);
void			draw_point(t_game *game, t_coord_f64 pos, int size, uint32_t color);

int is_a_wall_vue(t_wall_inter inter)
{
	if (inter.text1 && !(inter.text1->type & TRANSPARENCY))
		return (1);
	if (inter.text2 && !(inter.text2->type & TRANSPARENCY))
		return (1);
	return (0);
}

// 1 x
// 0 y
t_inter set_inter(int res, t_intersect xInter, t_intersect yInter)
{
	if (res)
		return ((t_inter){xInter.point, xInter.nb_step, yInter.nb_step});
	return ((t_inter){yInter.point, xInter.nb_step, yInter.nb_step});
}

t_inter get_intersect(t_game *game, double alpha, double tan_a)
{
	t_intersect xInter = get_init_x(game, alpha, tan_a);
	t_intersect yInter = get_init_y(game, alpha, tan_a);

	double xDist = get_distance2(game, xInter.point);
	double yDist = get_distance2(game, yInter.point);
	while (1)
	{
		if (xDist < yDist)
		{
			if (is_a_wall_vue(get_wall(game, xInter.point)))
				return ((t_inter){xInter.point, xInter.nb_step, yInter.nb_step});
			xInter = get_step_x(xInter, alpha, tan_a);
			xDist = get_distance2(game, xInter.point);
		}
		else
		{
			if (is_a_wall_vue(get_wall(game, yInter.point)))
				return ((t_inter){yInter.point, xInter.nb_step, yInter.nb_step});
			yInter = get_step_y(yInter, alpha, tan_a);
			yDist = get_distance2(game, yInter.point);
		}
	}
}
