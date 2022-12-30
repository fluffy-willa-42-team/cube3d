/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:49:55 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:51:33 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include "thenormforcedmetodothis.h"

void	draw_pixel_skybox(t_game *game, t_coord_i32 pixel_pos, t_texture *t);

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
	uint32_t			parse_height;
	t_draw_pixel		b;

	if (!texture || !(texture->type & VALID))
		return ;
	if (texture->skybox_tex && texture->type & TRANSPARENCY && a.recursive)
		draw_wall_text(game, inter, texture->skybox_tex,
			(t_draw_wall){a.x, a.height, 0});
	if (texture->type & IMAGE)
	{
		b.ratio = set_f64(1, (double) texture->image->height / (a.height * 2));
		b.offset = (inter.x - (int)(float) inter.x) * texture->image->width
			+ (inter.y - (int)(float) inter.y) * texture->image->height;
	}
	if (a.height > 400000000)
		a.height = 400000000;
	parse_height = a.height;
	if (parse_height >= WIN_HEIGHT / 2)
		parse_height = WIN_HEIGHT / 2 - 1;
	b.i = a.height - parse_height - 1;
	while (++b.i < a.height + parse_height)
	{
		draw_pixel_wall(game, set_i32(a.x, WIN_HEIGHT / 2 - a.height + b.i),
			texture, b);
	}
}
