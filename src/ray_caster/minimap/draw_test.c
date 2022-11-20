/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:11:40 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 13:33:17 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

void draw_line_s(t_mlx_param *param, t_coord_f64 a, t_coord_f64 b, int32_t color);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a);
double 	prot_tan(double alpha);

int is_equal(double a, double b);

void draw_rectangle_s(t_game *game, t_coord_i32 coord, uint32_t color)
{
	const int si = game->param.minimap_size;

	draw_rectangle(&game->param, set_f64(coord.x * si, coord.y * si), set_i32(si, si), color);
}

void draw_test(t_game *game, double alpha)
{
	t_inter inter = get_intersect(game, game->player.coord, alpha, prot_tan(alpha));
	draw_line_s(&game->param, game->player.coord, inter.point, 0xfcba03AA);
	
	t_intersect xInter;

	xInter.point = inter.point;
	xInter.wall = set_i32(inter.wall.x, (int) inter.point.y + (int []){-1, 0}[0 <= alpha && alpha < PI]);
	xInter.prev_wall = set_i32(inter.wall.x, (int) inter.point.y + (int []){0, -1}[0 <= alpha && alpha < PI]);
	draw_rectangle_s(game, xInter.wall, 0x770055FF);
	draw_rectangle_s(game, xInter.prev_wall, 0x775500FF);
	
}