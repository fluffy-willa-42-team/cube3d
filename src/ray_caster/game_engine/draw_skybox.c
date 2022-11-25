/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:27:25 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 17:13:17 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

uint32_t	get_skybox_pixel(t_game *game, t_coord_i32 pixel_pos,
				t_texture *texture)
{
	uint32_t	x;

	x = pixel_pos.x + (texture->image->width * 4)
		* (game->player.alpha / PI2);
	if (x >= texture->image->width * 4)
		x -= texture->image->width * 4;
	return (get_pixel_image(texture,
			x, pixel_pos.y, set_f64(
				0.25,
				(double) texture->image->height / WIN_HEIGHT
			)
		));
}

void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos,
		t_texture *texture)
{
	if (texture->type & IMAGE)
		put_pixel(game, pixel_pos.x, pixel_pos.y, 
			get_skybox_pixel(game, pixel_pos, texture)
			);
	else
		put_pixel(game, pixel_pos.x, pixel_pos.y, texture->color);
}
