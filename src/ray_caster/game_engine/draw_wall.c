/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:26 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 16:35:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <stdio.h>

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);
int				is_equal(double a, double b);

void	exchange_textures(t_wall_inter *wall)
{
	void *tmp;
	
	tmp = wall->chunk1;
	wall->chunk1 = wall->chunk2;
	wall->chunk2 = tmp;
	tmp = wall->text1;
	wall->text1 = wall->text2;
	wall->text2 = tmp;
}

int is_transparent(t_texture *text)
{
	return (!text || text->type & TRANSPARENCY);
}

void	draw_pixel_wall(t_game *game, t_coord_i32 pos, t_texture *texture)
{
	if (texture->type & IMAGE)
		put_pixel(game, pos.x, pos.y, 0xFF0000FF);
	else
		put_pixel(game, pos.x, pos.y, texture->color);
}

void	draw_wall_text(t_game *game, t_texture *texture, uint32_t x, double height)
{
	if (!texture)
		return ;
	uint32_t parse_heigth = height;
	if (parse_heigth >= MIDDLE_OF_SCREEN)
		parse_heigth = MIDDLE_OF_SCREEN;
	for (uint32_t i = height - parse_heigth; i < height + parse_heigth ; i++)
		draw_pixel_wall(game, set_i32(x, MIDDLE_OF_SCREEN - height + i), texture);
}

void	draw_wall(t_game *game, uint32_t x, t_coord_f64 inter, double height)
{
	t_wall_inter wall = get_wall(game, inter);
	
	if ((is_equal(inter.y, (int) (float) inter.y) && inter.y > game->player.pos.y)
		|| (is_equal(inter.x, (int) (float) inter.x) && inter.x > game->player.pos.x))
		exchange_textures(&wall);
	if (!is_transparent(wall.text1))
		draw_wall_text(game, wall.text1, x, height);
	else if (is_transparent(wall.text1) && !is_transparent(wall.text2))
	{
		draw_wall_text(game, wall.text2, x, height);
		draw_wall_text(game, wall.text1, x, height);
	}
}