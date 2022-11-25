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

double		loop_len(double n, double len);
double		prot_tan(double alpha);
t_chunk		*get_chunk(t_game *game, t_coord_i32 coord);
t_inter		get_intersect(t_game *game, double alpha, double tan_a);

void draw_point(t_game *game, t_coord_f64 pos, int size, uint32_t color)
{
	draw_rectangle(game,
		set_f64(pos.x * game->param.minimap_size - size, pos.y * game->param.minimap_size - size),
		set_i32(size * 2, size * 2),
		color
	);
}

void draw_rectangle_s(t_game *game, t_coord_f64 pos, uint32_t color)
{
	draw_rectangle(game,
		set_f64(pos.x * game->param.minimap_size, pos.y * game->param.minimap_size),
		set_i32(game->param.minimap_size, game->param.minimap_size),
		color
	);
}

void draw_line_s(t_game *game, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	draw_line(game,
		set_f64(a.x * game->param.minimap_size, a.y * game->param.minimap_size),
		set_f64(b.x * game->param.minimap_size, b.y * game->param.minimap_size),
		color
	);
}

void	draw_elem(t_game *game, int32_t x, int32_t y)
{
	t_chunk	*chunk = get_chunk(game, set_i32(x, y));
	if (chunk->north) draw_line_s(game, set_f64(x, y), 		set_f64(x + 1, y),	 	0x21634caa);
	if (chunk->south) draw_line_s(game, set_f64(x, y + 1), 	set_f64(x + 1, y + 1),	0x21634caa);
	if (chunk->east)  draw_line_s(game, set_f64(x + 1, y), 	set_f64(x + 1, y + 1), 	0x21634caa);
	if (chunk->west)  draw_line_s(game, set_f64(x, y),		set_f64(x, y + 1), 		0x21634caa);
}

void	draw_transparency(t_game *game, uint32_t x, t_inter inter, double alpha, double tan_a);

void draw_ray(t_game *game, uint32_t color, double alpha)
{
	double tan_a = prot_tan(alpha);

	t_inter test = get_intersect(game, alpha, tan_a);

	draw_line_s(game, game->player.pos, test.point, color);
}

int draw_minimap(t_game *game)
{
	t_map *map	= &game->map;

	for (uint32_t y = 0; y < map->height; y++)
	{
		for (uint32_t x = 0; x < map->width; x++)
		{
			if (
				get_chunk(game, set_i32(x, y))
				&& get_chunk(game, set_i32(x, y))->floor
				&& !(get_chunk(game, set_i32(x, y))->floor->type & SKYBOX)
			)
			draw_rectangle_s(game, set_f64(x, y), 0x222222FF);
		}
	}
	draw_ray(game, 0xffff0022, game->player.alpha);
	float i = 0.001;
	while (i < FOV_ANG_1_2)
	{
		draw_ray(game, 0xffff0022, loop_len(game->player.alpha - i,	PI2));
		draw_ray(game, 0xffff0022, loop_len(game->player.alpha + i,	PI2));
		i += 0.001;
	}
	for (uint32_t y = 0; y < map->height; y++)
		for (uint32_t x = 0; x < map->width; x++)
			draw_elem(game, x, y);
	draw_point(game, game->player.pos, game->param.minimap_point_size, 0xFF00FFFF);



	return (1);
}
