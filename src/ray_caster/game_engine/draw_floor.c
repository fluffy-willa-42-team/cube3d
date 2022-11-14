/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/11/14 14:50:19 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

void draw_floor(t_game *game, int y)
{
	// double dist;
	// double dist2;
	
	// t_coord_f64 cosin = set_f64(
	// 	cos(alpha),
	// 	sin(alpha)
	// );
	//            PROJ_DIST / cos(player.alpha - alpha)
	// double test = PROJ_DIST / (game->player.cosin.x * cosin.x + game->player.cosin.y * cosin.y);

	double rayDirX0 = game->player.cosin.x - game->player.plane.x;
	double rayDirY0 = game->player.cosin.y - game->player.plane.y;
	double rayDirX1 = game->player.cosin.x + game->player.plane.x;
	double rayDirY1 = game->player.cosin.y + game->player.plane.y;


	double dist = game->player.z * WIN_HEIGHT / (y - MDDL_SCRN_HGTH);
	t_coord_f64 step = set_f64(
		dist * (rayDirX1 - rayDirX0) / WIN_WIDTH,
		dist * (rayDirY1 - rayDirY0) / WIN_WIDTH
	);
	t_coord_f64 pos = set_f64(
		game->player.coord.x + dist * rayDirX0,
		game->player.coord.y + dist * rayDirY0
	);
	(void) step;
	(void) pos;
	

	for(int x = 0; x < WIN_WIDTH; x++)
	{
		t_chunk *chunk = get_chunk(game, set_i32(pos.x, pos.y));
			
		if (chunk && chunk->floor && chunk->floor->type == IMAGE)
		{
			put_pixel(&game->param, x, y,
				get_pixel_image(chunk->floor,
					(pos.x - (int) pos.x) * chunk->floor->image->width,
					(pos.y - (int) pos.y) * chunk->floor->image->height,
					set_f64(1, 1)
				)
			);
		}
		pos = add_f64(pos, step);
	}

		// t_chunk *chunk2 = get_chunk(game, set_i32(pos2.x, pos2.y));

		// if (chunk2 && chunk2->ceiling && chunk2->ceiling->type == IMAGE)
		// {
		// 	put_pixel(&game->param, x, y,
		// 		get_pixel_image(chunk2->ceiling,
		// 			(pos2.x - (int) pos2.x) * chunk2->ceiling->image->width,
		// 			(pos2.y - (int) pos2.y) * chunk2->ceiling->image->height,
		// 			set_f64(1, 1)
		// 		)
		// 	);
		// }
}
