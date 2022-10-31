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

t_intersect	get_init_x(t_player *player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_player *player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect get_step_x(t_intersect prev, double alpha, double tan_a);
t_intersect get_step_y(t_intersect prev, double alpha, double tan_a);

/**
 * @brief Checks if point given is at a wall
 * 
 * @return 0 if not, 1 if yes, -1 if out 
 */
int is_wall2(t_game *game, t_intersect inter)
{
	if (0 <= inter.wall.x && inter.wall.x < game->map.width
		&& 0 <= inter.wall.y && inter.wall.y < game->map.height)
		return (game->map.array[inter.wall.y][inter.wall.x]);
	return (-1);
}

double dist(t_coord_f64 a, t_coord_f64 b)
{
	return (fabs(a.x - b.x) + fabs(a.y - b.y));
}
// return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));

t_intersect get_intersect2(t_game *game, t_player *player, double alpha)
{
	const t_coord_i32 pos	= set_i32(player->coord.x, player->coord.y);
	const t_coord_f64 delta	= set_f64(player->coord.x - pos.x, player->coord.y - pos.y);
	const double tan_a = prot_tan(alpha);

	t_intersect xIntersect = get_init_x(player, delta, alpha, tan_a);
	t_intersect yIntersect = get_init_y(player, delta, alpha, tan_a);

	int x_is_wall = is_wall2(game, xIntersect);
	int y_is_wall = is_wall2(game, yIntersect);

	while (x_is_wall == 0)
	{
		xIntersect = get_step_x(xIntersect, alpha, tan_a);
		x_is_wall = is_wall2(game, xIntersect);
	}
	while (y_is_wall == 0)
	{
		yIntersect = get_step_y(yIntersect, alpha, tan_a);
		y_is_wall = is_wall2(game, yIntersect);
	}
	if (dist(player->coord, xIntersect.point) < dist(player->coord, yIntersect.point))
		return (xIntersect);
	return (yIntersect);
}



















void draw_ray(t_game *game, double alpha)
{
	t_intersect test = get_intersect2(game, &game->player, alpha);
	draw_line_s(&game->param, game->player.coord, test.point, 0xfcba03FF);
	if (is_wall2(game, test))
		draw_rectangle_s(&game->param, set_f64(test.wall.x, test.wall.y), set_i32(1, 1), 0xfcba03FF);

}

void draw_player(t_game *game)
{
	t_mlx_param *param	= &game->param;
	t_player *player	= &game->player;
	int si = MINIMAP_SIZE;

	draw_rectangle(param,
			set_f64(player->coord.x * si - 2, player->coord.y * si - 2),
			set_i32(4, 4), 0xFF00FFFF);
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
	draw_player(game);
	draw_ray(game, game->player.alpha);
	draw_ray(game, game->player.alpha - 0.15);
	draw_ray(game, game->player.alpha + 0.15);
	draw_ray(game, game->player.alpha - 0.25);
	draw_ray(game, game->player.alpha + 0.25);
	draw_ray(game, game->player.alpha - 0.35);
	draw_ray(game, game->player.alpha + 0.35);
	draw_ray(game, game->player.alpha - 0.5);
	draw_ray(game, game->player.alpha + 0.5);
	// printf("===================================\n");
	return (1);
}
