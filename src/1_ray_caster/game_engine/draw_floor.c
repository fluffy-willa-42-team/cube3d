/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:39:36 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include "thenormforcedmetodothis.h"
#include <math.h>

void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos,
			t_texture *texture);

void	draw_texture(
	t_game *game,
	t_texture *texture,
	t_coord_f64 floor_pos,
	t_coord_i32 pixel_pos
)
{
	if (!texture)
		return ;
	if (texture->skybox_tex && texture->type & TRANSPARENCY)
		draw_pixel_skybox(game, pixel_pos, texture->skybox_tex);
	if (texture->type & SKYBOX)
		draw_pixel_skybox(game, pixel_pos, texture);
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

void	draw_floor_plus(
	t_game *game,
	t_coord_i32 px,
	t_draw_floor a,
	double dist
)
{
	double				ratio;
	double				floor_dist;
	t_coord_f64			pos;
	t_chunk				*chunk;

	ratio = (1.0 + ((a.rest_to_draw - px.y) / a.height_drawn));
	floor_dist = dist / a.cos_a_minus_pa / ratio;
	pos = set_f64(
			game->player.pos.x + a.cosin.x * floor_dist,
			game->player.pos.y + a.cosin.y * floor_dist
			);
	chunk = get_chunk(game, set_i32(pos.x, pos.y));
	if (!chunk)
		return ;
	draw_texture(game, chunk->floor, pos, set_i32(px.x, WIN_HEIGHT - px.y - 1));
	draw_texture(game, chunk->ceiling, pos, set_i32(px.x, px.y));
}

void	draw_floor(
	t_game *game,
	int32_t	x,
	double alpha,
	t_draw_floor2 a
)
{
	int32_t				y;
	const t_draw_floor	b = {
		set_f64(cos(alpha), sin(alpha)),
		game->player.cosin.x * cos(alpha) + game->player.cosin.y * sin(alpha),
		WIN_HEIGHT / 2 - a.height_drawn + 2,
		a.height_drawn
	};

	y = 0;
	while (y < (int32_t) b.rest_to_draw)
	{
		draw_floor_plus(game, set_i32(x, y), b, a.dist);
		y++;
	}
}
