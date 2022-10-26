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

void put_pixel(t_mlx_param *param, int32_t x, int32_t y, uint32_t color)
{
	if (0 <= x && x < param->width && 0 <= y && y < param->height)
		mlx_put_pixel(param->img, x, y, color);
}

void draw_rectangle(t_mlx_param *param, t_coord_f64 point, t_coord_i32 size, uint32_t color)
{
	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
			put_pixel(param, point.x + i, point.y + j, color);
}

void draw_line(t_mlx_param *param, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	float step;
	float dx;
	float dy;

	dx = (b.x - a.x);
	dy = (b.y - a.y);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	int i = 1;
	while (i <= step) {
		put_pixel(param, a.x, a.y, color);
		a.x = a.x + dx;
		a.y = a.y + dy;
		i = i + 1;
	}
}
