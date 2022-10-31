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

t_intersect get_intersect(t_game *game, t_player *player, double alpha);

void draw_line_s(t_mlx_param *param, t_coord_f64 a, t_coord_f64 b, int32_t color)
{
	return (draw_line(param,
		set_f64(a.x * MINIMAP_SIZE, a.y * MINIMAP_SIZE),
		set_f64(b.x * MINIMAP_SIZE, b.y * MINIMAP_SIZE),
		color
	));
}

void draw_rectangle_s(t_mlx_param *param, t_coord_f64 point, t_coord_i32 size, uint32_t color)
{
	for (int i = 0; i < size.x * MINIMAP_SIZE; i++)
		for (int j = 0; j < size.y * MINIMAP_SIZE; j++)
			put_pixel(param, point.x * MINIMAP_SIZE + i, point.y * MINIMAP_SIZE + j, color);
}

void draw_ray(t_game *game, double alpha)
{
	t_intersect test = get_intersect(game, &game->player, alpha);
	draw_line_s(&game->param, game->player.coord, test.point, 0xfcba0355);
	draw_rectangle_s(&game->param, set_f64(test.wall.x, test.wall.y), set_i32(1, 1), 0xfcba03FF);
}

double loop_len(double n, double len)
{
	if (len == 0)
		return (n);
	while (n > len)
		n -= len;
	while (n < 0)
		n += len;
	return (n);
}

void draw_player(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_player *player	= &game->player;
	int si = MINIMAP_SIZE;

	draw_rectangle(param,
		set_f64(player->coord.x * si - 2, player->coord.y * si - 2),
		set_i32(4, 4), 0xFF00FFFF
	);
}

int draw_minimap(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_map *map			= &game->map;
	int si = MINIMAP_SIZE;

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
	draw_ray(game, loop_len(game->player.alpha, 		PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.02,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.02,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.04,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.04,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.06,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.06,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.08,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.08,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.10,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.10,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.12,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.12,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.14,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.14,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.16,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.16,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.18,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.18,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.20,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.20,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.22,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.22,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.24,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.24,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.26,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.26,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.28,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.28,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.30,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.30,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.32,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.32,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.34,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.34,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.36,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.36,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.38,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.38,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.40,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.40,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.42,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.42,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.44,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.44,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.46,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.46,	PI2));
	draw_ray(game, loop_len(game->player.alpha - 0.48,	PI2));
	draw_ray(game, loop_len(game->player.alpha + 0.48,	PI2));
	// printf("===================================\n");
	return (1);
}
