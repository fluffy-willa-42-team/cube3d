/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/25 17:27:39 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* struct_set() */
#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

int	init_map(t_parser *data)
{
	t_chunk	tmp;
	int		err;

	data->index = 0;
	printf("[%d]\n", data->index);//TODO REMOVE
	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_size.x * data->map_size.y)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	err = EXIT_SUCCESS ;
	while (err == EXIT_SUCCESS)
	{
		err = get_next_chunk(data, &tmp);
		if (err == EXIT_SUCCESS)
		{
			if (!v_add(&data->map, DEFAULT, &tmp))
				return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
		}
		else if (err == EXIT_FAILURE)
			return (ret_print(EXIT_FAILURE, "//TODO"));
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the chunk coord, `t_chunk.coor.{x,y}`
 * 
 * @param data 
 */
void	set_chunk_coord(t_parser *data)
{
	const int	max = data->map_size.x * data->map_size.y;
	int			index;
	t_coord_i32	coor;
	t_chunk		*tmp;

	index = 0;
	struct_set(&coor, sizeof(coor));
	while (index < max)
	{
		if (coor.x >= data->map_size.x)
		{
			coor.x = 0;
			coor.y++;
		}
		tmp = get_chunk_pars(data, coor);
		tmp->coord.x = coor.x;
		tmp->coord.y = coor.y;
		coor.x++;
		index++;
	}
}

/*
void	t_map_debug(t_parser *data)
{
	const int	max = data->map_size.x * data->map_size.y;
	int			index;
	t_coord_i32	coor;
	t_chunk	*tmp;

	index = 0;
	struct_set(&coor, sizeof(coor));
	while (index < max)
	{
		if (coor.x >= data->map_size.x)
		{
			coor.x = 0;
			coor.y++;
		}
		printf("(%d)x(%d)\n", coor.x, coor.y);
		tmp = get_chunk_pars(data, coor);
		if (tmp->type == WHITE_SPACE_CHUNK)
		{
			printf("[ , , ,]\n[ , , ,]\n[ , , ,]\n[ , , ,]\n");
		}
		else
		{
			printf("[%c,%c,.]\n[%c,%c,.]\n[%c,%c,.]\n[ %d, %d]\n\n",
			tmp->ceiling ? (tmp->ceiling->token ? tmp->ceiling->token : '.') : '.' ,
			tmp->north ? (tmp->north->token ? tmp->north->token : '.') : '.' ,

			tmp->west ? (tmp->west->token ? tmp->west->token : '.') : '.' ,
			tmp->east ? (tmp->east->token ? tmp->east->token : '.') : '.' ,
			
			tmp->floor ? (tmp->floor->token ? tmp->floor->token : '.') : '.' ,
			tmp->south ? (tmp->south->token ? tmp->south->token : '.') : '.',

			tmp->coord.x,
			tmp->coord.y
			);
		}
		coor.x++;
		index++;
	}
}
*/

/**
 * @brief 
 * 
 * @note In the first time we skip the `cube separator sequence string`, we
 *       increment the `data->cube_map` pointer.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	store_map(t_parser *data)
{
	if (set_map_size(data) || init_map(data))
		return (EXIT_FAILURE);
	set_chunk_coord(data);
	// t_map_debug(data);//TODO REMOVE
	
	// printf("{{\n%s\n}}\n",data->cube_map);printf("map size [%dx%d]\n", data->map_size.x,data->map_size.y);
	return (EXIT_SUCCESS);
}
