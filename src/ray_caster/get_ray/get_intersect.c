/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 11:30:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>
#include <stdio.h>

#include "mlx_utils.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

t_intersect	get_init_x(t_game *game, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_game *game, t_coord_f64 delta, double alpha, double tan_a);
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


t_intersect get_intersect(t_game *game, double alpha, double tan_a)
{
	const t_coord_f64 delta	= set_f64(
		game->player.coord.x - (int) game->player.coord.x,
		game->player.coord.y - (int) game->player.coord.y
	);

	t_intersect xIntersect = get_init_x(game, delta, alpha, tan_a);
	t_intersect yIntersect = get_init_y(game, delta, alpha, tan_a);

	double xDist = get_distance2(game, xIntersect.point);
	double yDist = get_distance2(game, yIntersect.point);
	while (1)
	{
		if (xDist < yDist)
		{
			if (is_a_wall_vue(get_wall(game, xIntersect.point)))
				return (xIntersect);
			xIntersect = get_step_x(xIntersect, alpha, tan_a);
			xDist = get_distance2(game, xIntersect.point);
		}
		else
		{
			if (is_a_wall_vue(get_wall(game, yIntersect.point)))
				return (yIntersect);
			yIntersect = get_step_y(yIntersect, alpha, tan_a);
			yDist = get_distance2(game, yIntersect.point);
		}
	}
	return (xIntersect);
}
