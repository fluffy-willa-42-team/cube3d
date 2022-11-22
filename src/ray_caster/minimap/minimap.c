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
double 	prot_tan(double alpha);

void draw_line_s(t_game *game, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	return (draw_line(game,
		set_f64(a.x * game->param.minimap_size, a.y * game->param.minimap_size),
		set_f64(b.x * game->param.minimap_size, b.y * game->param.minimap_size),
		color
	));
}

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

void	draw_elem(t_game *game, int32_t x, int32_t y)
{
	if (game->map.array[y][x] != 's')
	{
		t_chunk	*chunk = get_chunk(game, set_i32(x, y));
		if (chunk->north) draw_line_s(game, set_f64(x, y), 		set_f64(x + 1, y),	 	0x21634cFF);
		if (chunk->south) draw_line_s(game, set_f64(x, y + 1), 	set_f64(x + 1, y + 1),	0x21634cFF);
		if (chunk->east)  draw_line_s(game, set_f64(x + 1, y), 	set_f64(x + 1, y + 1), 	0x21634cFF);
		if (chunk->west)  draw_line_s(game, set_f64(x, y),		set_f64(x, y + 1), 		0x21634cFF);
	}
}

t_intersect get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a);

void draw_rectangle_s(t_game *game, t_coord_f64 pos, uint32_t color)
{
	draw_rectangle(game, set_f64(
			pos.x * game->param.minimap_size,
			pos.y * game->param.minimap_size
		),
		set_i32(
			game->param.minimap_size,
			game->param.minimap_size
		),
		color
	);
}

int draw_minimap(t_game *game)
{
	t_map *map	= &game->map;
	int si		= game->param.minimap_size;

	for (uint32_t y = 0; y < map->height; y++)
	{
		for (uint32_t x = 0; x < map->width; x++)
		{
			if (game->map.array[y][x] == 's')
				draw_rectangle_s(game, set_f64(x, y), 0x770000FF);
			else
				draw_rectangle_s(game, set_f64(x, y), 0x222222FF);
		}
	}
	for (uint32_t y = 0; y < map->height; y++)
		for (uint32_t x = 0; x < map->width; x++)
			draw_elem(game, x, y);
	draw_rectangle(game,
		set_f64(game->player.coord.x * si - 2, game->player.coord.y * si - 2),
		set_i32(4, 4), 0xFF00FFFF
	);
	draw_line_s(game, game->player.coord, add_f64(game->player.coord, game->player.cosin), 0xFF00FFFF);
	// get_intersect(game, game->player.coord, game->player.alpha, prot_tan(game->player.alpha));
	return (1);
}
