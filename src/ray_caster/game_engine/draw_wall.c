/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:26 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:39:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include "thenormforcedmetodothis.h"
#include <stdio.h>

t_bool	is_equal(double a, double b);
void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos,
			t_texture *texture);

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

void	draw_pixel_wall(
	t_game *game,
	t_coord_i32 pos,
	t_texture *texture,
	t_draw_pixel a
)
{
	if (texture->type & SKYBOX)
		draw_pixel_skybox(game, pos, texture);
	else if (texture->type & IMAGE)
		put_pixel(game, pos.x, pos.y,
			get_pixel_image(texture, a.offset, a.i, a.ratio));
	else
		put_pixel(game, pos.x, pos.y, texture->color);
}

void	draw_wall_text(
	t_game *game,
	t_coord_f64 inter,
	t_texture *texture,
	t_draw_wall a
)
{
	t_coord_f64			ratio;
	double				offset;
	uint32_t			parse_height;
	uint32_t			i;

	if (!texture || !(texture->type & VALID))
		return ;
	if (texture->skybox_tex && texture->type & TRANSPARENCY && a.recursive)
		draw_wall_text(game, inter, texture->skybox_tex,
			(t_draw_wall){a.x, a.height, 0});
	if (texture->type & IMAGE)
	{
		ratio = set_f64(1, (double) texture->image->height / (a.height * 2));
		offset = (inter.x - (int)(float) inter.x) * texture->image->width
			+ (inter.y - (int)(float) inter.y) * texture->image->height;
	}
	if (a.height > 400000000)
		a.height = 400000000;
	parse_height = a.height;
	if (parse_height >= WIN_HEIGHT / 2)
		parse_height = WIN_HEIGHT / 2 - 1;
	i = a.height - parse_height;
	while (i < a.height + parse_height)
	{
		draw_pixel_wall(game, set_i32(a.x, WIN_HEIGHT / 2 - a.height + i),
			texture, (t_draw_pixel){ratio, offset, i});
		i++;
	}
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
