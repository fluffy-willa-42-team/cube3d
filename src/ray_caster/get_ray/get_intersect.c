/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/11/19 12:17:53 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>
#include <stdio.h>

#include "mlx_utils.h"

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);
t_texture *get_wall_texture(t_chunk *chunk, t_coord_f64 inter);

t_intersect	get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);

int check_validity_text(t_chunk *chunk, t_coord_f64 inter)
{
	t_texture *text = get_wall_texture(chunk, inter);

	return (text && !(text->type & TRANSPARENCY));
}

/**
 * @brief Checks if point given is at a wall
 * 
 * @return 0 if not, 1 if yes, -1 if out 
 */
int is_wall(t_game *game, t_intersect *inter)
{
	t_chunk *next = get_chunk(game, inter->wall);
	t_chunk *prev = get_chunk(game, inter->prev_wall);
	
	if (!prev && !next)
		return (-1);
	if (check_validity_text(prev, inter->point))
	{
		inter->wall = inter->prev_wall;
		return (1);
	}
	else if (check_validity_text(next, inter->point))
		return (1);
	return (0);
}

double dist(t_coord_f64 a, t_coord_f64 b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}

t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a)
{
	const t_coord_i32 pos	= set_i32(player.x, player.y);
	const t_coord_f64 delta	= set_f64(player.x - pos.x, player.y - pos.y);

	t_intersect xIntersect = get_init_x(player, delta, alpha, tan_a);
	t_intersect yIntersect = get_init_y(player, delta, alpha, tan_a);

	int x_is_wall = is_wall(game, &xIntersect);
	int y_is_wall = is_wall(game, &yIntersect);

	while (x_is_wall == 0)
	{
		xIntersect = get_step_x(xIntersect, alpha, tan_a);
		x_is_wall = is_wall(game, &xIntersect);
	}
	while (y_is_wall == 0)
	{
		yIntersect = get_step_y(yIntersect, alpha, tan_a);
		y_is_wall = is_wall(game, &yIntersect);
	}
	if (dist(player, xIntersect.point) < dist(player, yIntersect.point))
		return ((t_inter){xIntersect.point, xIntersect.wall});
	return ((t_inter){yIntersect.point, yIntersect.wall});
}
