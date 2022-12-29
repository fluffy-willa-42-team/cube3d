/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:26 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:51:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include "thenormforcedmetodothis.h"
#include <stdio.h>

t_bool	is_equal(double a, double b);
void	draw_wall_text(t_game *g, t_coord_f64 i, t_texture *t, t_draw_wall a);

void	exchange_textures(t_wall_inter *wall)
{
	void	*tmp;

	tmp = wall->chunk1;
	wall->chunk1 = wall->chunk2;
	wall->chunk2 = tmp;
	tmp = wall->text1;
	wall->text1 = wall->text2;
	wall->text2 = tmp;
}

t_bool	is_transparent(t_texture *text)
{
	return (!text
		|| (text->type & TRANSPARENCY && !text->skybox_tex));
}

void	draw_wall(t_game *game, uint32_t x, t_coord_f64 inter, double height)
{
	t_wall_inter	wall;

	wall = get_wall(game, inter);
	if ((is_equal(inter.y, (int)(float) inter.y)
		&& inter.y > game->player.pos.y)
		|| (is_equal(inter.x, (int)(float) inter.x)
		&& inter.x > game->player.pos.x))
		exchange_textures(&wall);
	if (!is_transparent(wall.text1))
		draw_wall_text(game, inter, wall.text1, (t_draw_wall){x, height, 1});
	else if (is_transparent(wall.text1) && !is_transparent(wall.text2))
	{
		draw_wall_text(game, inter, wall.text2, (t_draw_wall){x, height, 1});
		draw_wall_text(game, inter, wall.text1, (t_draw_wall){x, height, 1});
	}
}

void	draw_wall_trans(
	t_game *game,
	uint32_t x,
	t_coord_f64 inter,
	double height
)
{
	t_wall_inter	wall;

	wall = get_wall(game, inter);
	if ((is_equal(inter.y, (int)(float) inter.y)
		&& inter.y > game->player.pos.y)
		|| (is_equal(inter.x, (int)(float) inter.x)
		&& inter.x > game->player.pos.x))
		exchange_textures(&wall);
	if (wall.text1 || wall.text2)
	{
		height = WIN_HEIGHT / 10 * game->param.hob_mult / height;
		draw_wall_text(game, inter, wall.text2, (t_draw_wall){x, height, 1});
		draw_wall_text(game, inter, wall.text1, (t_draw_wall){x, height, 1});
	}
}
