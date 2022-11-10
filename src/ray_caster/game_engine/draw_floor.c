/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:10 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

t_chunk get_chunk(t_game *game, t_coord_i32 coord);

void draw_floor(t_game *game, int x, double alpha, int heigth_drawn)
{
	double dist;
	
	double proj_dist = WIN_WIDTH / 2 / tan(FOV_ANGLE / 2);


	int rest_to_draw = MDDL_SCRN_HGTH - heigth_drawn + 1;
	for (int32_t y = 0; y < rest_to_draw; y++)
	{
		// dist = 0.5 * proj_dist / (game->player.z - y) * WIN_WIDTH / WIN_HEIGHT;
		
		dist = 0.5 * proj_dist / (game->player.z * WIN_HEIGHT - y);
		// dist = dist * cos(alpha - game->player.alpha);
		t_coord_f64 pos = set_f64(
			game->player.coord.x + cos(alpha) * dist,
			game->player.coord.y + sin(alpha) * dist
		);

		t_chunk chunk = get_chunk(game, set_i32(pos.x, pos.y));
			
		if (chunk.floor && chunk.floor->type == IMAGE)
		{
			put_pixel(&game->param, x, WIN_HEIGHT - y,
				get_pixel_image(chunk.floor,
					(pos.x - (int) pos.x) * chunk.floor->image->width,
					(pos.y - (int) pos.y) * chunk.floor->image->height,
					set_f64(1, 1)
				)
			);
		}

		if (chunk.ceiling && chunk.ceiling->type == IMAGE)
		{
			put_pixel(&game->param, x, y,
				get_pixel_image(chunk.ceiling,
					(pos.x - (int) pos.x) * chunk.ceiling->image->width,
					(pos.y - (int) pos.y) * chunk.ceiling->image->height,
					set_f64(1, 1)
				)
			);
		}
		
	}
}
