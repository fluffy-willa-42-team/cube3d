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

void	put_pixel(t_game *game, int32_t x, int32_t y, uint32_t color)
{
	if (color != 0)
		mlx_put_pixel(game->param.img, x, y, color);
}

void	draw_rectangle(
	t_game *game,
	t_coord_f64 point,
	t_coord_i32 size,
	uint32_t color
)
{
	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
			put_pixel(game, point.x + i, point.y + j, color);
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
