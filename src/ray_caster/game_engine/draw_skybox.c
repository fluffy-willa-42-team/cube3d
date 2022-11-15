/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:27:25 by awillems          #+#    #+#             */
/*   Updated: 2022/11/15 12:25:12 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

#include <stdio.h>

// draw Skybox to be redone (Extremely expensive in performense)
void draw_skybox(t_game *game)
{
	if (game->skybox.type & VALID && game->skybox.type & IMAGE)
	{
		draw_image(game, &game->skybox,
			set_i32(
				(-game->player.alpha / PI2) * 4 * WIN_WIDTH,
				0
			),
			set_i32(
				WIN_WIDTH * 4,
				WIN_HEIGHT
			)
		);
		draw_image(game, &game->skybox,
			set_i32(
				(1 - game->player.alpha / PI2) * 4 * WIN_WIDTH,
				0
			),
			set_i32(
				WIN_WIDTH * 4,
				WIN_HEIGHT
			)
		);
	}
	else if (game->skybox.type & VALID && game->skybox.type & COLOR)
		draw_rectangle(&game->param, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), game->skybox.color);
	else
		draw_rectangle(&game->param, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), 0x000000FF);
}