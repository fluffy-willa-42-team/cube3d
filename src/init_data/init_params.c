/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:39:57 by awillems          #+#    #+#             */
/*   Updated: 2022/12/12 16:17:10 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "init_data.h"

t_param	init_params(void)
{
	t_param	params;

	params.mlx = NULL;
	params.win = NULL;
	params.img = NULL;
	params.hob_mult = 5;
	params.minimap_size = 8;
	params.minimap_point_size = 2;
	params.speed = 0.05;
	return (params);
}
