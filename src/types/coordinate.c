/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:50:02 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 11:44:04 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_coord_i32	init_coord_i32(void)
{
	t_coord_i32	res;

	res.x = 0;
	res.y = 0;
	return (res);
}

t_coord_f64	init_coord_f64(void)
{
	t_coord_f64	res;

	res.x = 0;
	res.y = 0;
	return (res);
}