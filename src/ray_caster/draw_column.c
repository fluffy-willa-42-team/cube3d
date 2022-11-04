/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:31:46 by awillems          #+#    #+#             */
/*   Updated: 2022/11/04 11:25:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "mlx_utils.h"

t_texture get_texture(t_game *game, int x, int y)
{
	(void) x;
	(void) y;
	return (game->temp);
}

t_coord_f64 get_texture_inter(t_intersect inter)
{
	if (is_equal(inter.point.x, inter.wall.x))
		return (set_f64(0, inter.point.y - inter.wall.y));
	if (is_equal(inter.point.x, inter.wall.x + 1))
		return (set_f64(0, 1 - (inter.point.y - inter.wall.y)));
	if (is_equal(inter.point.y, inter.wall.y))
		return (set_f64(1 - (inter.point.x - inter.wall.x), 0));
	if (is_equal(inter.point.y, inter.wall.y + 1))
		return (set_f64(inter.point.x - inter.wall.x, 0));
	return (set_f64(0, 0));
}

/**
 * @param x 		pos x on screen
 * @param height 	Line Height
 */
void draw_column(t_game *game, t_intersect inter, uint32_t x, int32_t height)
{
	const t_texture texture = get_texture(game, inter.wall.x, inter.wall.y);
	const t_coord_f64 texture_inter = get_texture_inter(inter);

	if (texture.type == COLOR)
	{
		draw_rectangle(&game->param,
			set_f64(x, WIN_HEIGHT / 2 - height),
			set_i32(COLUMN_WIDTH, height * 2), 
			texture.color
		);
	}
	else if (texture.type == IMAGE && texture.image)
	{
		t_coord_f64 ratio = set_f64(1,
			(double) texture.image->height /( (double) height * 2)
		);
		double offset = texture_inter.x * texture.image->width
						+ texture_inter.y * texture.image->height;
		
		for (int i = 0; i < COLUMN_WIDTH; i++)
			for (int j = 0; j < height * 2; j++)
				put_pixel(&game->param, x + i, WIN_HEIGHT / 2 - height + j,
					get_pixel_image(texture, i + offset, j, ratio)
				);
		
	}
}
