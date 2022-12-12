/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:57:51 by awillems          #+#    #+#             */
/*   Updated: 2022/12/12 17:01:20 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

u_int32_t put_pixel_in_image(t_image *texture, uint32_t x, uint32_t y, uint32_t color)
{
	if (!texture || !texture->buffer)
		return (0);
	if (x >= texture->width || y >= texture->height)
		return (0);
	texture->buffer[y * texture->width + x] = color;
	return (1);
}

uint32_t *get_pixel_from_image(t_image *texture, uint32_t x, uint32_t y)
{
	if (!texture || !texture->buffer)
		return (0);
	if (x >= texture->width || y >= texture->height)
		return (0);
	return (&texture->buffer[y * texture->width + x]);
}
