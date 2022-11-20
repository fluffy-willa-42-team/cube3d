/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparent_wall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:59:24 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 12:47:24 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double get_distance(t_game *game, t_inter *inter);

void	draw_transparent_wall(t_game *game, t_inter *inter, double alpha, double tan_a)
{
	const double	origin_dist = get_distance(game, inter);

	(void) game;
	(void) inter;
	(void) alpha;
	(void) tan_a;
	(void) origin_dist;
	// t_intersect xInter;
}