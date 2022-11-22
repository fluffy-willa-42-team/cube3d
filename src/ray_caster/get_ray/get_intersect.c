/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 13:10:37 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>
#include <stdio.h>

#include "mlx_utils.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

t_intersect	get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);

double dist(t_coord_f64 a, t_coord_f64 b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
void draw_rectangle_s(t_game *game, t_coord_f64 pos, uint32_t color);

int is_a_wall(t_wall_inter inter)
{
	if (inter.text1 || inter.text2)
		return (1);
	return (0);
}

double get_distance(t_game *game, t_inter *inter);

t_intersect get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a)
{
	const t_coord_i32 pos	= set_i32(player.x, player.y);
	const t_coord_f64 delta	= set_f64(player.x - pos.x, player.y - pos.y);

	t_intersect xIntersect = get_init_x(player, delta, alpha, tan_a);
	t_intersect yIntersect = get_init_y(player, delta, alpha, tan_a);

	// xIntersect = get_step_x(xIntersect, alpha, tan_a);
	// yIntersect = get_step_y(yIntersect, alpha, tan_a);
	(void) game;
	(void) xIntersect;
	(void) yIntersect;
	t_wall_inter inter = get_wall(game, yIntersect.point);
	if (is_a_wall(inter))
	{
		if (inter.chunk1)
			draw_rectangle_s(game, set_f64(inter.chunk1->coord.x, inter.chunk1->coord.y), 0x00ff00ff);
		if (inter.chunk2)
			draw_rectangle_s(game, set_f64(inter.chunk2->coord.x, inter.chunk2->coord.y), 0x00ffffff);
	}
	
	return (xIntersect);
}
