/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/types/coordinate.c
/*   Created: 2022/10/19 14:50:02 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:56:56 by awillems         ###   ########.fr       */
=======
/*   Created: 2022/11/22 14:40:19 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:40:37 by mahadad          ###   ########.fr       */
>>>>>>> main:src/0_parser/c_cube_to_t_map/map/get_chunk.c
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

<<<<<<< HEAD:src/types/coordinate.c
t_coord_i32	init_i32(void)
=======
/**
 * @brief Get the `t_chunk` from the array with the coordinate `{x, y}`.
 * 
 * @return t_chunk* Return pointer from the array.
 */
t_chunk	*get_chunk(t_parser *data, int x, int y)
>>>>>>> main:src/0_parser/c_cube_to_t_map/map/get_chunk.c
{
	const int	index = (y * data->map_size.x) + x;

<<<<<<< HEAD:src/types/coordinate.c
	res.x = 0;
	res.y = 0;
	return (res);
}

t_coord_f64	init_f64(void)
{
	t_coord_f64	res;

	res.x = 0;
	res.y = 0;
	return (res);
}

t_coord_f64	set_f64(float x, float y)
{
	return ((t_coord_f64){x, y});
}

t_coord_i32	set_i32(float x, float y)
{
	return ((t_coord_i32){x, y});
}

t_coord_f64	add_f64(t_coord_f64 a, t_coord_f64 b)
{
	return ((t_coord_f64){
		a.x + b.x,
		a.y + b.y
	});
}
=======
	return (v_get(&data->map, index));
}
>>>>>>> main:src/0_parser/c_cube_to_t_map/map/get_chunk.c
