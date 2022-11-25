/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:24:28 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 11:58:51 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_chunk	*get_chunk(t_game *game, t_coord_i32 pos);
int		is_equal(double a, double b);

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter)
{
	t_wall_inter wall_inter;
	t_coord_i32 pos = set_i32((float) inter.x, (float) inter.y);

	wall_inter.text1 = NULL;
	wall_inter.text2 = NULL;
	wall_inter.chunk2 = NULL;
	wall_inter.chunk1 = get_chunk(game, set_i32(inter.x, inter.y));
	if (is_equal(inter.y, pos.y)) // NORTH-SOUTH
	{
		wall_inter.chunk2 = get_chunk(game, set_i32(pos.x, pos.y - 1));
		if (wall_inter.chunk1)
			wall_inter.text1 = wall_inter.chunk1->north;
		if (wall_inter.chunk2)
			wall_inter.text2 = wall_inter.chunk2->south;
	}
	else if (is_equal(inter.x, pos.x)) // EAST-WEST
	{
		wall_inter.chunk2 = get_chunk(game, set_i32(pos.x - 1, pos.y));
		if (wall_inter.chunk1)
			wall_inter.text1 = wall_inter.chunk1->west;
		if (wall_inter.chunk2)
			wall_inter.text2 = wall_inter.chunk2->east;
	}
	return (wall_inter);
}
