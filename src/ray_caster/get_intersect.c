/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/10/31 13:25:00 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>

t_intersect	get_init_x(t_player *player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_player *player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);

double prot_tan(double alpha)
{
	double res;

	res = tan(alpha);
	if (res >= 0 && res < 0.0001)
		res = 0.0001;
	else if (res <= -0 && res > -0.0001)
		res = -0.0001;
	return (res);
}

/**
 * @brief Checks if point given is at a wall
 * 
 * @return 0 if not, 1 if yes, -1 if out 
 */
int is_wall2(t_game *game, t_intersect inter)
{
	if (0 <= inter.wall.x && inter.wall.x < game->map.width
		&& 0 <= inter.wall.y && inter.wall.y < game->map.height)
		return (game->map.array[inter.wall.y][inter.wall.x]);
	return (-1);
}

double dist(t_coord_f64 a, t_coord_f64 b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}

t_intersect get_intersect(t_game *game, t_player *player, double alpha)
{
	const t_coord_i32 pos	= set_i32(player->coord.x, player->coord.y);
	const t_coord_f64 delta	= set_f64(player->coord.x - pos.x, player->coord.y - pos.y);
	const double tan_a = prot_tan(alpha);

	t_intersect xIntersect = get_init_x(player, delta, alpha, tan_a);
	t_intersect yIntersect = get_init_y(player, delta, alpha, tan_a);

	int x_is_wall = is_wall2(game, xIntersect);
	int y_is_wall = is_wall2(game, yIntersect);

	while (x_is_wall == 0)
	{
		xIntersect = get_step_x(xIntersect, alpha, tan_a);
		x_is_wall = is_wall2(game, xIntersect);
	}
	while (y_is_wall == 0)
	{
		yIntersect = get_step_y(yIntersect, alpha, tan_a);
		y_is_wall = is_wall2(game, yIntersect);
	}
	if (dist(player->coord, xIntersect.point) < dist(player->coord, yIntersect.point))
		return (xIntersect);
	return (yIntersect);
}
