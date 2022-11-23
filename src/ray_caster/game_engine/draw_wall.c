/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:26 by awillems          #+#    #+#             */
/*   Updated: 2022/11/23 15:21:31 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);

void	draw_wall(t_game *game, uint32_t x, t_coord_f64 inter, double height)
{
	t_wall_inter textures = get_wall(game, inter);
	uint32_t	parse_heigth;
	
	(void) game;
	(void) x;
	(void) inter;
	(void) textures;
	parse_heigth = height;
	if (parse_heigth >= MIDDLE_OF_SCREEN)
		parse_heigth = MIDDLE_OF_SCREEN;
	for (uint32_t i = height - parse_heigth; i < height + parse_heigth ; i++)
	{
		// draw_pixel_wall(game, texture,
		// 	set_i32(x, MIDDLE_OF_SCREEN - height + i),
		// 	(t_gpiximg){ratio, (int32_t) offset, i}
		// );
		put_pixel(game, x, MIDDLE_OF_SCREEN - height + i, 0xFF0000FF);
	}
}