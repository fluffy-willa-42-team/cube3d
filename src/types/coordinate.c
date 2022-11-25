/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:50:02 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:56:56 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_coord_i32	init_i32(void)
{
	t_coord_i32	res;

	res.x = 0;
	res.y = 0;
	return (res);
}

t_coord_f64	init_f64(void)
{
	t_coord_f64	res;

	res.x = 0;
	res.y = 0;
	return (res);
}

t_coord_f64	set_f64(float x, float y)
{
	return ((t_coord_f64){x, y});
}

t_coord_i32	set_i32(float x, float y)
{
	return ((t_coord_i32){x, y});
}

t_coord_f64	add_f64(t_coord_f64 a, t_coord_f64 b)
{
	return ((t_coord_f64){
		a.x + b.x,
		a.y + b.y
	});
}
