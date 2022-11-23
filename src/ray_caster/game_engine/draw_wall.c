/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:26 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 16:27:37 by awillems         ###   ########.fr       */
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

void	draw_wall_text(t_game *game, t_texture *text, uint32_t x, double height)
{
	(void) text;
	if (!text)
		return ;
	uint32_t parse_heigth = height;
	if (parse_heigth >= MIDDLE_OF_SCREEN)
		parse_heigth = MIDDLE_OF_SCREEN;
	for (uint32_t i = height - parse_heigth; i < height + parse_heigth ; i++)
	{
		put_pixel(game, x, MIDDLE_OF_SCREEN - height + i, 0xFF0000FF);
	}
}

int is_transparent(t_texture *text)
{
	return (!text || text->type & TRANSPARENCY);
}

// cas 1 : le mur devant est n'est pas transparent
// cas 2 : le mur devant est transparent ou nexiste pas et le mur derriere est
// 		   solide
void	draw_wall(t_game *game, uint32_t x, t_coord_f64 inter, double height)
{
	t_wall_inter wall = get_wall(game, inter);
	
	if ((is_equal(inter.y, (int) inter.y) && inter.y > game->player.pos.y)
		|| (is_equal(inter.x, (int) inter.x) && inter.x > game->player.pos.x))
		exchange_textures(&wall);
	if (!is_transparent(wall.text1))
		draw_wall_text(game, wall.text1, x, height);
	else if (is_transparent(wall.text1) && !is_transparent(wall.text2))
	{
		draw_wall_text(game, wall.text2, x, height);
		draw_wall_text(game, wall.text1, x, height);
	}
}