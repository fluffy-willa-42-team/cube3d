/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:01:07 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 11:01:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include "mlx_utils.h"

#include <stdio.h>

t_coord_f64	init_coord_f64(void);

t_coord_f64 c_f64(float x, float y)
{
	return ((t_coord_f64){x, y});
}

t_coord_i32 c_i32(float x, float y)
{
	return ((t_coord_i32){x, y});
}

void draw_player(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_player *player	= &game->player;
	int si = MINIMAP_SIZE;

	draw_rectangle(param,
			c_f64(player->coord.x * si - si/2, player->coord.y * si - si/2),
			c_i32(si, si), 0xFF00FFFF);
	draw_line(param, c_f64(player->coord.x * si, player->coord.y * si),
		c_f64((player->coord.x + player->dir.x) * si,
		(player->coord.y + player->dir.y) * si), 0x00FF00FF);
}

int draw_minimap(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_map *map			= &game->map;
	int si = MINIMAP_SIZE;

	// draw_rectangle(param, init_coord_f64(),
	// 	(t_coord_i32){param->width, param->height}, 0x111111FF);
	for (int y = 0; y < map->width; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			if (map->array[y][x])
				draw_rectangle(param, (t_coord_f64){x * si, y * si},
					(t_coord_i32){si, si}, 0x770000FF);
			else
				draw_rectangle(param, (t_coord_f64){x * si, y * si},
					(t_coord_i32){si, si}, 0x222222FF);
		}

	}
	draw_player(game);
	return (1);
}