/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:31:46 by awillems          #+#    #+#             */
/*   Updated: 2022/11/02 13:32:22 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>

#include "mlx_utils.h"

uint32_t get_color_for_direction(const t_intersect inter)
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

t_texture get_texture(t_game *game, int x, int y)
{
	(void) x;
	(void) y;
	return (game->temp);
}

void draw_simple(t_game *game, t_intersect inter, uint32_t x, int32_t height)
{
	draw_rectangle(&game->param,
		set_f64(x, WIN_HEIGHT / 2 - height),
		set_i32(COLUMN_WIDTH, height * 2), 
		get_color_for_direction(inter)
	);
}

/**
 * @brief 
 * 
 * @param game 
 * @param inter 	
 * @param x 		pos x on screen
 * @param height 	Line Height
 */
void draw_column(t_game *game, t_intersect inter, uint32_t x, int32_t height)
{
	t_texture texture = get_texture(game, inter.wall.x, inter.wall.y);
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
		// uint32_t ratio_texture_pixel = texture.image->height / height;
		// uint32_t ratio_visible = height / WIN_HEIGHT / 2;
		// for (uint32_t i = 0; i < ratio_visible; i++)
		// {
		// 	put_pixel(&game->param, x, i, get_pixel_image());
		// 	i++;
		// }
		// printf("%f")
	}
}
