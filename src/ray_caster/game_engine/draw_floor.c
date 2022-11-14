/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:08:12 by awillems          #+#    #+#             */
/*   Updated: 2022/11/14 13:30:14 by awillems         ###   ########.fr       */
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

	t_coord_f64 plane = set_f64(
		0.66,
		0.66
	);

	double dist = game->player.z * WIN_HEIGHT / (y - MDDL_SCRN_HGTH);
	t_coord_f64 step = set_f64(
		dist * 2 * plane.x / WIN_WIDTH,
		dist * 2 * plane.y / WIN_WIDTH
	);
	t_coord_f64 pos = set_f64(
		game->player.coord.x + dist * (game->player.cosin.x - plane.x),
		game->player.coord.y + dist * (game->player.cosin.y - plane.y)
	);
	printf("%f %f\n", pos.x, pos.y);
	(void) step;
	(void) pos;
	

	for(int x = 0; x < WIN_WIDTH; x++)
	{
		pos = add_f64(pos, step);
		t_chunk *chunk = get_chunk(game, set_i32(pos.x, pos.y));
			
		if (chunk && chunk->floor && chunk->floor->type == IMAGE)
		{
			put_pixel(&game->param, x, WIN_HEIGHT - y,
				get_pixel_image(chunk->floor,
					(pos.x - (int) pos.x) * chunk->floor->image->width,
					(pos.y - (int) pos.y) * chunk->floor->image->height,
					set_f64(1, 1)
				)
			);
		}
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
