/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:39:57 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 11:45:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "init_data.h"

t_param	init_params(void)
{
	t_param params;

	params.mlx = NULL;
	params.img = NULL;
	params.hob_mult = 5;
	params.minimap_size = 8;
	params.minimap_point_size = 2;
	return (params);
}
