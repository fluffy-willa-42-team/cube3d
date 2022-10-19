/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:50:02 by awillems          #+#    #+#             */
/*   Updated: 2022/10/19 14:53:38 by awillems         ###   ########.fr       */
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