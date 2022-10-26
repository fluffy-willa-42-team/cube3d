/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:50:02 by awillems          #+#    #+#             */
/*   Updated: 2022/10/26 11:54:40 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_coord_i32	init_coord_i32(void)
{
	t_coord_i32	res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	return (res);
}

t_coord_f32	init_coord_f32(void)
{
	t_coord_f32	res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	return (res);
}
