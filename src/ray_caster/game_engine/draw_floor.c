/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 10:42:22 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos, t_texture *texture);

void	draw_top_or_bottom(
	t_game *game,
	t_texture *texture,
	t_coord_f64 floor_pos,
	t_coord_i32 pixel_pos
)
{
	if (texture)
	{
		if (texture->type & SKYBOX && texture->type & IMAGE)
			draw_pixel_skybox(game, pixel_pos, &game->skybox);
		else if (texture->type & IMAGE)
		{
			put_pixel(game, pixel_pos.x, pixel_pos.y,
				get_pixel_image(texture,
					(floor_pos.x - (int) floor_pos.x) * texture->image->width,
					(floor_pos.y - (int) floor_pos.y) * texture->image->height,
					set_f64(1, 1)
				)
			);
		}
		else
		{
			put_pixel(game, pixel_pos.x, pixel_pos.y, texture->color);
		}
	}
}

void draw_floor(t_game *game, int x, double alpha, double heigth_drawn, double dist)
{
	const t_coord_f64 cosin = set_f64(
		cos(alpha),
		sin(alpha)
	);
	const double cos_a_minus_pa = game->player.cosin.x * cosin.x + game->player.cosin.y * cosin.y;
	double rest_to_draw = MIDDLE_OF_SCREEN - heigth_drawn + 2;
	for (int32_t y = 0; y < (int32_t) rest_to_draw; y++)
	{
		double ratio = (1.0 + ((rest_to_draw - y) / heigth_drawn));
		double floor_dist = dist / cos_a_minus_pa / ratio;
		t_coord_f64 pos = set_f64(
			game->player.pos.x + cosin.x * floor_dist,
			game->player.pos.y + cosin.y * floor_dist
		);
		t_chunk *chunk = get_chunk(game, set_i32(pos.x, pos.y));
		if (!chunk)
			continue ;
		draw_top_or_bottom(game, chunk->floor, pos, set_i32(x, WIN_HEIGHT - y - 1));
		draw_top_or_bottom(game, chunk->ceiling, pos, set_i32(x, y));
	}
}
