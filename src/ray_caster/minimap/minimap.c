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

#include "ray_caster.h"
#include "mlx_utils.h"

#include <stdio.h>

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a);
double 	prot_tan(double alpha);

void draw_line_s(t_mlx_param *param, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	return (draw_line(param,
		set_f64(a.x * param->minimap_size, a.y * param->minimap_size),
		set_f64(b.x * param->minimap_size, b.y * param->minimap_size),
		color
	));
}

void draw_ray(t_game *game, double alpha)
{
	t_inter test = get_intersect(game, game->player.coord, alpha, prot_tan(alpha));
	draw_line_s(&game->param, game->player.coord, test.point, 0xfcba03AA);
}

int draw_minimap(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_map *map			= &game->map;
	int si = param->minimap_size;

	for (uint32_t y = 0; y < map->height; y++)
	{
		for (uint32_t x = 0; x < map->width; x++)
		{
			if (map->array[y][x] == 's')
				draw_rectangle(param, (t_coord_f64){x * si, y * si},
					(t_coord_i32){si, si}, 0x770000FF);
			else if (map->array[y][x] != ' ')
				draw_rectangle(param, (t_coord_f64){x * si, y * si},
					(t_coord_i32){si, si}, 0x21634cFF);
			else
				draw_rectangle(param, (t_coord_f64){x * si, y * si},
					(t_coord_i32){si, si}, 0x222222FF);
		}
	}
	draw_rectangle(param,
		set_f64(game->player.coord.x * si - 2, game->player.coord.y * si - 2),
		set_i32(4, 4), 0xFF00FFFF
	);
	draw_ray(game, loop_len(game->player.alpha, 		PI2));
	float i = 0.001;
	while (i < game->stat.fov_angle_1_2)
	{
		draw_ray(game, loop_len(game->player.alpha - i,	PI2));
		draw_ray(game, loop_len(game->player.alpha + i,	PI2));
		i += 0.001;
	}
	draw_line_s(&game->param, game->player.coord, add_f64(game->player.coord, game->player.cosin), 0xFF00FFFF);
	return (1);
}
