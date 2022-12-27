/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:34:42 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 14:37:27 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	change_value_f(double *ptr, double incr, double min, double max)
{
	if (min <= *ptr + incr && *ptr + incr <= max)
		*ptr += incr;
}

void	change_value_i(uint32_t *ptr, uint32_t incr, uint32_t min, uint32_t max)
{
	if (min <= *ptr + incr && *ptr + incr <= max)
		*ptr += incr;
}
