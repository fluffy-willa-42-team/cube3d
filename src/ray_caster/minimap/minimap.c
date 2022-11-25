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

double		loop_len(double n, double len);
double		prot_tan(double alpha);
t_inter		get_intersect(t_game *game, double alpha, double tan_a);

void	draw_side(t_game *game, int32_t x, int32_t y)
{
	t_chunk	*chunk;

	chunk = get_chunk(game, set_i32(x, y));
	if (chunk->north)
		draw_mini_line(game, set_f64(x, y), set_f64(x + 1, y), 0x21634caa);
	if (chunk->south)
		draw_mini_line(game, set_f64(x, y + 1), set_f64(x + 1, y + 1),
			0x21634caa);
	if (chunk->east)
		draw_mini_line(game, set_f64(x + 1, y), set_f64(x + 1, y + 1),
			0x21634caa);
	if (chunk->west)
		draw_mini_line(game, set_f64(x, y), set_f64(x, y + 1), 0x21634caa);
}

void	draw_ray(t_game *game, uint32_t color, double alpha)
{
	double	tan_a;
	t_inter	test;

	tan_a = prot_tan(alpha);
	test = get_intersect(game, alpha, tan_a);
	draw_mini_line(game, game->player.pos, test.point, color);
}

void	draw_minimap(t_game *game)
{
	t_map	*map = &game->map;
	float	i;

	for (uint32_t y = 0; y < map->height; y++)
	{
		for (uint32_t x = 0; x < map->width; x++)
		{
			if (
				get_chunk(game, set_i32(x, y))
				&& get_chunk(game, set_i32(x, y))->floor
				&& !(get_chunk(game, set_i32(x, y))->floor->type & SKYBOX)
			)
				draw_mini_rect(game, set_f64(x, y), 0x222222FF);
		}
	}
	draw_ray(game, 0xffff0022, game->player.alpha);
	i = 0.001;
	while (i < FOV_ANG_1_2)
	{
		draw_ray(game, 0xffff0022, loop_len(game->player.alpha - i,	PI2));
		draw_ray(game, 0xffff0022, loop_len(game->player.alpha + i,	PI2));
		i += 0.001;
	}
	for (uint32_t y = 0; y < map->height; y++)
		for (uint32_t x = 0; x < map->width; x++)
			draw_side(game, x, y);
	draw_mini_point(game, game->player.pos, game->param.minimap_point_size,
		0xFF00FFFF);
}
