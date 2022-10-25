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

int draw_minimap(t_game *game)
{
	t_mlx_param *param = &game->param;
	t_map *map = &game->map;



	draw_rectangle(param, init_coord_f64(), (t_coord_i32){param->width, param->height}, 0x111111FF);
	for (int y = 0; y < map->width; y++)
		for (int x = 0; x < map->width; x++)
			if (map->array[y][x])
				draw_rectangle(param,
					(t_coord_f64){x * MINIMAP_SIZE, y * MINIMAP_SIZE},
					(t_coord_i32){MINIMAP_SIZE, MINIMAP_SIZE}, 0x770000FF);
	// draw_line(param, (t_coord_f64) {0.0f, 0.0f}, (t_coord_f64) {64.0f, 64.0f}, 0xFF0000FF);
	return (1);
}