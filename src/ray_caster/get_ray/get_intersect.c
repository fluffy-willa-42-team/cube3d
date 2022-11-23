/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 13:01:26 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_chunk		*get_chunk(t_game *game, t_coord_i32 coord);

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect	get_init_x(t_game *game, double alpha, double tan_a);
t_intersect	get_init_y(t_game *game, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);


t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
void			draw_rectangle_s(t_game *game, t_coord_f64 pos, uint32_t color);
void			draw_point(t_game *game, t_coord_f64 pos, int size, uint32_t color);

int is_a_wall_vue(t_wall_inter inter)
{
	if (inter.text1 && !(inter.text1->type & TRANSPARENCY))
		return (1);
	if (inter.text2 && !(inter.text2->type & TRANSPARENCY))
		return (1);
	return (0);
}

t_inter get_intersect(t_game *game, double alpha, double tan_a)
{
	t_intersect xInter = get_init_x(game, alpha, tan_a);
	t_intersect yInter = get_init_y(game, alpha, tan_a);

	double xDist = get_distance(game, xInter.point);
	double yDist = get_distance(game, yInter.point);
	while (1)
	{
		if (xDist < yDist)
		{
			if (is_a_wall_vue(get_wall(game, xInter.point)))
				return ((t_inter){xInter.point, xInter, yInter});
			xInter = get_step_x(xInter, alpha, tan_a);
			xDist = get_distance(game, xInter.point);
		}
		else
		{
			if (is_a_wall_vue(get_wall(game, yInter.point)))
				return ((t_inter){yInter.point, xInter, yInter});
			yInter = get_step_y(yInter, alpha, tan_a);
			yDist = get_distance(game, yInter.point);
		}
	}
}
