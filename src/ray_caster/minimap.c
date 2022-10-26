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
#include <math.h>

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

double prot_tan(double alpha)
{
	double res;

	res = tan(alpha);
	if (res >= 0 && res < 0.0001)
		res = 0.0001;
	else if (res <= -0 && res > -0.0001)
		res = -0.0001;
	return (res);
}

// Return the index of the chunk in the map with the pos and the angle given
// opt = 0 : Horzontal  / x
// opt = 1 : Vertical   / y
// can give negative !!!!
t_coord_f64 get_wall_coord(t_coord_f64 p, double alpha, int opt)
{
	return (set_f64(
		(int) (p.x - ((int []){0, 1}[PI1_2 <= alpha && alpha < PI3_2]) * !opt),
		(int) (p.y - ((int []){1, 0}[0 <= alpha && alpha < PI]) * opt))
	);
}

int is_wall(t_game *game, t_coord_f64 a)
{
	if (0 <= a.x && a.x < game->map.width && 0 <= a.y && a.y < game->map.height)
		return (game->map.array[(int) a.y][(int) a.x]);
	return (-1);
}

t_coord_f64 get_intersect(t_game *game)
{
	t_player	*player	= &game->player;
	t_coord_i32 pos		= set_i32(player->coord.x, player->coord.y);
	t_coord_f64 delta	= set_f64(player->coord.x - pos.x, player->coord.y - pos.y);
	double tan_a = prot_tan(player->alpha);

	t_coord_f64 xIntercept = set_f64(
		pos.x + (int []){1, 0}[PI1_2 <= player->alpha && player->alpha < PI3_2],
		pos.y + delta.y + (int []){1, -1}[PI1_2 <= player->alpha && player->alpha < PI3_2] * delta.x * tan_a
	);
	t_coord_f64 yIntercept = set_f64(
		pos.x + delta.x + (int []){-1, 1}[0 <= player->alpha && player->alpha < PI] * delta.y / tan_a,
		pos.y + (int []){0, 1}[0 <= player->alpha && player->alpha < PI]
	);
	(void) delta;
	(void) xIntercept;

	draw_line_s(&game->param, player->coord, xIntercept, 0x452679FF);
	draw_line_s(&game->param, player->coord, yIntercept, 0xE3c611FF);
	if (is_wall(game, get_wall_coord(xIntercept, player->alpha, 0)))
		draw_rectangle_s(&game->param, get_wall_coord(xIntercept, player->alpha, 0), set_i32(1, 1), 0x452679FF);
	if (is_wall(game, get_wall_coord(yIntercept, player->alpha, 1)))
		draw_rectangle_s(&game->param, get_wall_coord(yIntercept, player->alpha, 1), set_i32(1, 1), 0xE3c611FF);
	// printf("(%d, %d) (%f, %f)\n", pos.x, pos.y, delta.x, delta.y);
	return (init_f64());
}

void draw_ray(t_game *game)
{
	t_coord_f64 x = get_intersect(game);
	// printf("%f %f\n", x.x, x.y);
	(void) x;
}

void draw_player(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_player *player	= &game->player;
	int si = MINIMAP_SIZE;

	draw_rectangle(param,
			set_f64(player->coord.x * si - si/2, player->coord.y * si - si/2),
			set_i32(si, si), 0xFF00FFFF);
	draw_line(param, set_f64(player->coord.x * si, player->coord.y * si),
		set_f64((player->coord.x + player->dir.x) * si,
		(player->coord.y + player->dir.y) * si), 0x00FF00FF);
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
	draw_ray(game);
	draw_player(game);
	return (1);
}
