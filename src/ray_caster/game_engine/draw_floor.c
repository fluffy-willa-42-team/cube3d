/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/11/16 10:09:11 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

static void	draw_top_or_bottom(
	t_game *game,
	t_texture *texture,
	t_coord_f64 floor_pos,
	t_coord_i32 pixel_pos
)
{
	if (texture)
	{
		if (texture->type & IMAGE)
		{
			put_pixel(&game->param, pixel_pos.x, pixel_pos.y,
				get_pixel_image(texture,
					(floor_pos.x - (int) floor_pos.x) * texture->image->width,
					(floor_pos.y - (int) floor_pos.y) * texture->image->height,
					set_f64(1, 1)
				)
			);
		}
		else
		{
			put_pixel(&game->param, pixel_pos.x, pixel_pos.y, texture->color);
		}
	}
}

void draw_floor(t_game *game, int x, double alpha, int heigth_drawn)
{
	const t_coord_f64 cosin = set_f64(
		cos(alpha),
		sin(alpha)
	);
	//            PROJ_DIST / cos(player.alpha - alpha) * game->param.hob_mult;
	const double proj_dist = PROJ_DIST / cos(alpha - game->player.alpha) * game->param.hob_mult / 1.77;
	//  PROJ_DIST / (game->player.cosin.x * cosin.x + game->player.cosin.y * cosin.y) * game->param.hob_mult;
	double dist;

	int rest_to_draw = MDDL_SCRN_HGTH - heigth_drawn + 1;
	for (int32_t y = 0; y < rest_to_draw; y++)
	{
		dist = proj_dist / (y - game->player.z * WIN_HEIGHT);
		t_coord_f64 pos = set_f64(
			game->player.coord.x + cosin.x * dist,
			game->player.coord.y + cosin.y * dist
		);

		t_chunk *chunk = get_chunk(game, set_i32(pos.x, pos.y));
		if (!chunk)
			continue ;
		draw_top_or_bottom(game, chunk->floor,		pos, set_i32(x, WIN_HEIGHT - y));
		draw_top_or_bottom(game, chunk->ceiling,	pos, set_i32(x, y));
	}
}
