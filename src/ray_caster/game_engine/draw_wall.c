/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:31:46 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 12:33:47 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "mlx_utils.h"

int is_equal(double a, double b);

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);
t_texture *get_wall_texture(const t_chunk *chunk, t_coord_f64 inter);

void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos);

/**
 * @brief 
 * 
 * @param texture The given texture we want to show
 * @param pixel_pos Position of the pixel we ask for
 * @param image_data Is not an intersection but random data for get_pixel_image
 * but the norms doesn't let me get more than 4 params...
 */
void	draw_pixel_wall(t_game *game, const t_texture *texture, t_coord_i32 pixel_pos, t_gpiximg image_data)
{
	
	if (texture->type & SKYBOX)
		draw_pixel_skybox(game, set_i32(pixel_pos.x, pixel_pos.y));
	else if (texture->type & IMAGE)
		put_pixel(&game->param, pixel_pos.x, pixel_pos.y,
			get_pixel_image(texture, image_data.offset, image_data.i, image_data.ratio)
		);
	else
		put_pixel(&game->param, pixel_pos.x, pixel_pos.y, texture->color);
}

t_coord_f64 get_texture_inter(t_inter *inter)
{
	if (is_equal(inter->point.x, inter->wall.x))
		return (set_f64(0, inter->point.y - inter->wall.y));
	if (is_equal(inter->point.x, inter->wall.x + 1))
		return (set_f64(0, 1 - (inter->point.y - inter->wall.y)));
	if (is_equal(inter->point.y, inter->wall.y))
		return (set_f64(1 - (inter->point.x - inter->wall.x), 0));
	if (is_equal(inter->point.y, inter->wall.y + 1))
		return (set_f64(inter->point.x - inter->wall.x, 0));
	return (set_f64(0, 0));
}

/**
 * @param x 		pos x on screen
 * @param height 	Line Height
 */
void	draw_wall(t_game *game, t_inter *inter, uint32_t x, uint32_t height)
{
	const t_texture		*texture		= get_wall_texture(get_chunk(game, inter->wall), inter->point);
	const t_coord_f64	texture_inter	= get_texture_inter(inter);
	uint32_t			parse_heigth;
	t_coord_f64			ratio;
	double 				offset;
	
	if (!texture || !(texture->type & VALID))
		return ;
	if (texture->type & IMAGE && texture->image)
	{
		ratio = set_f64(1, (double) texture->image->height / (height * 2));
		offset = texture_inter.x * texture->image->width
				+ texture_inter.y * texture->image->height;
	}
	if (!(texture->type & VALID))
		return ;
	parse_heigth = height;
	if (parse_heigth >= game->stat.middle_screen_y)
		parse_heigth = game->stat.middle_screen_y;
	for (uint32_t i = height - parse_heigth; i < height + parse_heigth ; i++)
	{
		draw_pixel_wall(game, texture,
			set_i32(x, game->stat.middle_screen_y - height + i),
			(t_gpiximg){ratio, (int32_t) offset, i}
		);
	}
}
