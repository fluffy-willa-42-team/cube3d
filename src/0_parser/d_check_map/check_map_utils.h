/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/29 16:35:07 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_MAP_UTILS_H
# define CHECK_MAP_UTILS_H

typedef enum e_wall
{
	NW		= 0b0000,
	W2EMPTY	= 0b0001,
	W2		= 0b0100,
	W1		= 0b1000,
}			t_wall;

int		is_clip(t_texture *tmp);
t_chunk	*get(t_parser *data, t_coord_i32 pos);
int		check_x(t_parser *data);
int		check_y(t_parser *data);

#endif //CHECK_MAP_UTILS_H
