/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:46:34 by awillems          #+#    #+#             */
/*   Updated: 2022/10/19 14:48:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_texture	init_texture(void)
{
	t_texture	res;

	res.type = 0;
	res.image = NULL;
	res.color = 0;
	return (res);
}
