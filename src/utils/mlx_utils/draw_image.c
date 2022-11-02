/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:54:48 by awillems          #+#    #+#             */
/*   Updated: 2022/11/02 15:59:28 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void put_pixel(t_mlx_param *param, int32_t x, int32_t y, uint32_t color);

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static uint32_t	get_pixel_image(t_texture texture, int x, int y, t_coord_f64 ratio)
{
	uint8_t *ptr = &texture.image->pixels[
		(((int) (y * ratio.y)) * texture.image->width + ((int) (x * ratio.x))) * 4
	];
	return (get_rgba(*ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3)));
}

void draw_image(t_game *game, t_texture texture, t_coord_i32 pos, t_coord_i32 size)
{
	t_coord_f64 ratio = set_f64(
		(double) texture.image->width / (double) size.x,
		(double) texture.image->height / (double) size.y
	);
	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
			put_pixel(&game->param, pos.x + i, pos.y + j,
				get_pixel_image(texture, i, j, ratio));
}
