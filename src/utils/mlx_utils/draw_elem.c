/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:10:55 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 13:10:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "math.h"
#include <stdio.h>

u_int32_t	put_pixel_in_image(t_image *texture,
				uint32_t x, uint32_t y, uint32_t color);

void	put_pixel(t_game *game, int32_t x, int32_t y, uint32_t color)
{
	if (color != 0xff000000)
		put_pixel_in_image(game->param.img, x, y, color);
}

void	draw_rectangle(
	t_game *game,
	t_coord_f64 point,
	t_coord_i32 size,
	uint32_t color
)
{
	t_coord_i32	iter;

	iter = set_i32(-1, -1);
	while (++iter.x < size.x)
	{
		while (++iter.y < size.y)
		{
			put_pixel(game, point.x + iter.x, point.y + iter.y, color);
		}
		iter.y = -1;
	}
}

void	draw_line(t_game *game, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	float	step;
	float	dx;
	float	dy;
	int		i;

	dx = (b.x - a.x);
	dy = (b.y - a.y);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	i = 1;
	while (i <= step)
	{
		put_pixel(game, a.x, a.y, color);
		a.x = a.x + dx;
		a.y = a.y + dy;
		i = i + 1;
	}
}
