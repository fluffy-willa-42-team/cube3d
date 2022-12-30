/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:40:18 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "thenormforcedmetodothis.h"
#include <stdio.h>

double		get_distance(t_game *game, t_coord_f64 pos);
t_intersect	get_init_x(t_game *game, double alpha, double tan_a);
t_intersect	get_init_y(t_game *game, double alpha, double tan_a);
t_intersect	get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect	get_step_y(t_intersect prev, double alpha, double tan_a);

t_bool	is_in_map(t_game *game, t_coord_f64 point)
{
	return (0 <= point.x && point.x < game->map.width
		&& 0 <= point.y && point.y < game->map.height);
}

t_bool	is_a_wall_vue(t_game *game, t_coord_f64 inter_point)
{
	const t_wall_inter	inter = get_wall(game, inter_point);

	if (inter.text1
		&& !(inter.text1->type & TRANSPARENCY && !inter.text1->skybox_tex))
		return (TRUE);
	if (inter.text2
		&& !(inter.text2->type & TRANSPARENCY && !inter.text2->skybox_tex))
		return (TRUE);
	return (FALSE);
}

t_bool	is_next_step_good(
	t_game *game,
	t_intersect *inter,
	double *dist,
	t_get_inter2 a
)
{
	if (!is_in_map(game, inter->point)
		|| is_a_wall_vue(game, inter->point))
		return (TRUE);
	*inter = a.func(*inter, a.alpha, a.tan_a);
	*dist = get_distance(game, inter->point);
	return (FALSE);
}

t_inter	get_intersect(t_game *game, t_ang_param a)
{
	t_intersect	x_inter;
	t_intersect	y_inter;
	double		x_dist;
	double		y_dist;

	x_inter = get_init_x(game, a.alpha, a.tan_a);
	y_inter = get_init_y(game, a.alpha, a.tan_a);
	x_dist = get_distance(game, x_inter.point);
	y_dist = get_distance(game, y_inter.point);
	while (TRUE)
	{
		if (x_dist < y_dist)
		{
			if (is_next_step_good(game, &x_inter, &x_dist,
					(t_get_inter2){a.alpha, a.tan_a, get_step_x}))
				return ((t_inter){x_inter.point, x_inter, y_inter});
		}
		else if (is_next_step_good(game, &y_inter, &y_dist,
				(t_get_inter2){a.alpha, a.tan_a, get_step_y}))
			return ((t_inter){y_inter.point, x_inter, y_inter});
	}
}
