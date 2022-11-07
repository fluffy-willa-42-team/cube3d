/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:31:46 by awillems          #+#    #+#             */
/*   Updated: 2022/11/07 13:14:39 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "mlx_utils.h"

int is_equal(double a, double b);

uint32_t get_color_for_direction(const t_inter inter)
{
	if (inter.wall.x - 0.00001 < inter.point.x && inter.point.x < inter.wall.x + 0.00001)
		return (0xeb4034FF);
	if (inter.wall.x + 0.99999 < inter.point.x && inter.point.x < inter.wall.x + 1.00001)
		return (0x4287f5FF);
	if (inter.wall.y - 0.00001 < inter.point.y && inter.point.y < inter.wall.y + 0.00001)
		return (0xfcba03FF);
	if (inter.wall.y + 0.99999 < inter.point.y && inter.point.y < inter.wall.y + 1.00001)
		return (0x32a852FF);
	return (0);
}

void draw_simple(t_game *game, t_inter inter, uint32_t x, int32_t height)
{
	draw_rectangle(&game->param,
		set_f64(x, WIN_HEIGHT / 2 - height),
		set_i32(COLUMN_WIDTH, height * 2), 
		get_color_for_direction(inter)
	);
}


t_texture get_texture(t_game *game, int x, int y)
{
	(void) x;
	(void) y;
	return (game->temp);
}

t_coord_f64 get_texture_inter(t_inter inter)
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
void draw_column(t_game *game, t_inter inter, uint32_t x, int32_t height)
{
	const t_texture texture = get_texture(game, inter.wall.x, inter.wall.y);
	const t_coord_f64 texture_inter = get_texture_inter(inter);
	const int32_t	parse_heigth = (int32_t []){height, WIN_HEIGHT}[height > WIN_HEIGHT];
	t_coord_f64 ratio;
	double 		offset;
	
	if (texture.type == IMAGE && texture.image)
	{
		ratio = set_f64(1,
			(double) texture.image->height /( (double) height * 2)
		);
		offset = texture_inter.x * texture.image->width
				+ texture_inter.y * texture.image->height;
	}
	
	for (int i = 0; i < COLUMN_WIDTH; i++)
	{
		for (int j = 0; j < parse_heigth * 2; j++)
		{
			if (texture.type == COLOR)
				put_pixel(&game->param, x + i, WIN_HEIGHT / 2 - height + j,
					texture.color
				);
			else
				put_pixel(&game->param, x + i, WIN_HEIGHT / 2 - height + j,
					get_pixel_image(texture, i + offset, j, ratio)
				);
		}
		
	}
}
