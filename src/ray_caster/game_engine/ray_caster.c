/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/10 11:54:40 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha);

void draw_skybox(t_game *game);

int32_t draw_wall(t_game *game, t_inter inter, uint32_t x, int32_t height);

static double distance(t_game *game, t_inter inter)
{
	return ((inter.point.x - game->player.coord.x) * game->player.delta.x
		+ (inter.point.y - game->player.coord.y) * game->player.delta.y);
}


// void	draw_floor(t_brain *b, double alpha, int y, double x)
// {
// 	t_fpoint	div;
// 	t_point		pos;
// 	float		dist;
// 	int			color;

// 	div.x = (double)b->map->bloc_size / 2;
// 	div.y = b->player->cam->proj_size.y / 2;
// 	while (y < b->ctx->height)
// 	{
// 		dist = (0.5 * b->player->cam->proj_dist) / ((y - player.z) - (div.y));
// 		pos.x = player.x + dist * cos(alpha);
// 		pos.y = player.y + dist * sin(alpha);
// 		color = pixel_get(b->map->floor, pos.x, pos.y);
// 		pixel_put(x, y, color, b->map->frame);
// 		y++;
// 	}
// }


t_chunk get_chunk(t_game *game, t_coord_i32 coord);

void draw_floor(t_game *game, int x, double alpha, int heigth_drawn)
{
	double dist;
	
	double proj_dist = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);


	int rest_to_draw = MDDL_SCRN_HGTH - heigth_drawn + 1;
	for (int32_t j = 0; j < rest_to_draw; j++)
	{
		double y = 1 - (double) j / WIN_HEIGHT;
		dist = (0.5 * proj_dist) / ((y - game->player.z) - WIN_HEIGHT);
		t_coord_f64 pos = set_f64(
			game->player.coord.x + cos(alpha) * dist,
			game->player.coord.y + sin(alpha) * dist
		);
		//draw Floors
		t_chunk chunk = get_chunk(game, set_i32(pos.x, pos.y));
			
		if (chunk.ceiling && chunk.ceiling->type == IMAGE)
		{
			put_pixel(&game->param, x, WIN_HEIGHT - j,
				get_pixel_image(chunk.ceiling,
					(pos.x - (int) pos.x) * chunk.ceiling->image->width,
					(pos.y - (int) pos.y) * chunk.ceiling->image->height,
					set_f64(1, 1)
				)
			);
		}
		// else if (chunk.ceiling && chunk.ceiling->type == COLOR)
		// {
			
		// }
		
	}
}

void ray_caster(t_game *game)
{
	double	angle;
	t_inter	inter;
	double	dist;
	
	draw_skybox(game);
	angle = game->player.alpha - FOV_ANGLE1_2 - FOV_INCRE;
	for (uint32_t i = 0; i < FOV_WIDTH; i++)
	{
		angle += FOV_INCRE;
		//draw Walls
		inter = get_intersect(game, game->player.coord, loop_len(angle, PI2));
		dist = distance(game, inter);
		int heigth_drawn = draw_wall(game, inter, i, HEIGTH_OF_BLOCK / dist);

		if (heigth_drawn >= WIN_HEIGHT - 1)
			continue ;
		
		draw_floor(game, i, angle, heigth_drawn);
		
		
	}
}