/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/10 19:05:11 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * //TODO
 * 
 * data.map_size.{x,y} /3 and store to map size
 * Make function util to read cube format
 * 
 */

int	set_chunk(t_chunk *chunk)
{
	(void)chunk;
	return (EXIT_SUCCESS);
}

int	init_map(t_parser *data)
{
	t_chunk	tmp;
	int		err;

	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_size.x * data->map_size.y)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	err = EXIT_SUCCESS ;
	while (err == EXIT_SUCCESS)
	{
		err = set_chunk(&tmp);
		if (err == EXIT_SUCCESS)
			if (!v_add(&data->map, DEFAULT, &tmp))
				return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param data Parser structure.
 * @return int 
 */
int	store_map(t_parser *data)
{
	(void)data;
	data->index = 0;
	while (mapchar(data) && (mapchar(data) == '~' || mapchar(data) == '\n'))
		data->index++;
	if (set_map_size(data) || init_map(data))
		return (EXIT_FAILURE);
	printf("{{\n%s\n}}\n",data->cube_map);printf("map size [%dx%d]\n", data->map_size.x,data->map_size.y);
	return (EXIT_SUCCESS);
}
