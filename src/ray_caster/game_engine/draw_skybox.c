/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:27:25 by awillems          #+#    #+#             */
/*   Updated: 2022/11/17 14:53:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

uint32_t get_skybox_pixel(t_game *game, t_coord_i32 pixel_pos)
{
	uint32_t x = pixel_pos.x
		+ (game->skybox.image->width * 4) * (game->player.alpha / PI2);
	if (x >= game->skybox.image->width * 4)
		x -= game->skybox.image->width * 4;
	
	return (get_pixel_image(&game->skybox,
		x,
		pixel_pos.y,
		set_f64(
			0.25,
			(double) game->skybox.image->height / WIN_HEIGHT
		)
	));
}

void draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos)
{
	if (game->skybox.type & IMAGE)
		put_pixel(&game->param, pixel_pos.x, pixel_pos.y, 
			get_skybox_pixel(game, pixel_pos)
		);
	else
		put_pixel(&game->param, pixel_pos.x, pixel_pos.y, game->skybox.color);
}
