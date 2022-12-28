/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:54:48 by awillems          #+#    #+#             */
/*   Updated: 2022/12/28 15:00:33 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		put_pixel(t_param *param, int32_t x, int32_t y, uint32_t color);
uint32_t	*get_pixel_from_image(t_image *texture, uint32_t x, uint32_t y);

uint32_t	get_pixel_image(
	const t_texture *texture,
	uint32_t x,
	uint32_t y,
	t_coord_f64 ratio
)
{
	if (!texture || !texture->image)
		return (0);
	if ((uint32_t)(y * ratio.y) >= texture->image->height
		|| (uint32_t)(x * ratio.x) >= texture->image->width)
		return (0);
	return (*(uint32_t *) get_pixel_from_image(texture->image,
			x * ratio.x, y * ratio.y));
}

void	draw_image(
	t_game *game,
	const t_texture *texture,
	t_coord_i32 pos,
	t_coord_i32 size
)
{
	t_coord_f64	ratio;
	t_coord_i32	iter;

	if (!texture || (texture->type & 0b1))
		return ;
	ratio = set_f64(
			(double) texture->image->width / (double) size.x,
			(double) texture->image->height / (double) size.y
			);
	iter = set_i32(-1, -1);
	while (++iter.x < size.x)
	{
		while (++iter.y < size.y)
			put_pixel(&game->param, pos.x + iter.x, pos.y + iter.y,
				get_pixel_image(texture, iter.x, iter.y, ratio));
		iter.y = -1;
	}
}
