/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 16:59:25 by awillems         ###   ########.fr       */
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

double get_distance2(t_game *game, t_coord_f64 pos)
{
	return ((pos.x - game->player.coord.x) * game->player.cosin.x
		+ (pos.y - game->player.coord.y) * game->player.cosin.y);
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

	for (int i = 0; i < 10; i++)
	{
		double xDist = get_distance2(game, xIntersect.point);
		double yDist = get_distance2(game, yIntersect.point);
		if (xDist < yDist)
		{
			if (is_a_wall(get_wall(game, xIntersect.point)))
			{
				printf("xWall found\n");
				return (xIntersect);
			}
			xIntersect = get_step_x(xIntersect, alpha, tan_a);
		}
		else
		{
			if (is_a_wall(get_wall(game, yIntersect.point)))
			{
				printf("yWall found\n");
				return (yIntersect);
			}
			yIntersect = get_step_x(yIntersect, alpha, tan_a);
		}
	}
	printf("None Found\n");
	return (xIntersect);
}
