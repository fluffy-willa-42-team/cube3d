/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:23:03 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 13:12:28 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

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

t_inter	get_intersect2(t_game *game, double alpha, double tan_a)
{
	t_get_inter	a;

	a = (t_get_inter){get_init_x(game, alpha, tan_a),
		get_init_y(game, alpha, tan_a),
		get_distance(game, a.x_inter.point),
		get_distance(game, a.y_inter.point)};
	while (TRUE)
	{
		if (a.x_dist < a.y_dist)
		{
			if (!is_in_map(game, a.x_inter.point)
				|| is_a_wall_vue(game, a.x_inter.point))
				return ((t_inter){a.x_inter.point, a.x_inter, a.y_inter});
			a.x_inter = get_step_x(a.x_inter, alpha, tan_a);
			a.x_dist = get_distance(game, a.x_inter.point);
		}
		else
		{
			if (!is_in_map(game, a.y_inter.point)
				|| is_a_wall_vue(game, a.y_inter.point))
				return ((t_inter){a.y_inter.point, a.x_inter, a.y_inter});
			a.y_inter = get_step_y(a.y_inter, alpha, tan_a);
			a.y_dist = get_distance(game, a.y_inter.point);
		}
	}
}


t_inter	get_intersect(t_game *game, double alpha, double tan_a)
{
	t_intersect	x_inter;
	t_intersect	y_inter;
	double		x_dist;
	double		y_dist;

	x_inter = get_init_x(game, alpha, tan_a);
	y_inter = get_init_y(game, alpha, tan_a);
	x_dist = get_distance(game, x_inter.point);
	y_dist = get_distance(game, y_inter.point);
	while (1)
	{
		if (x_dist < y_dist)
		{
			if (!is_in_map(game, x_inter.point)
				|| is_a_wall_vue(game, x_inter.point))
				return ((t_inter){x_inter.point, x_inter, y_inter});
			x_inter = get_step_x(x_inter, alpha, tan_a);
			x_dist = get_distance(game, x_inter.point);
		}
		else
		{
			if (!is_in_map(game, y_inter.point)
				|| is_a_wall_vue(game, y_inter.point))
				return ((t_inter){y_inter.point, x_inter, y_inter});
			y_inter = get_step_y(y_inter, alpha, tan_a);
			y_dist = get_distance(game, y_inter.point);
		}
	}
}
