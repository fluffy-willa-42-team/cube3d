/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/28 14:16:23 by mahadad          ###   ########.fr       */
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

//TODO REMOVE
/******************************************************************************/
/* */ // Get the red channel.
/* */ static int get_r(int rgba)
/* */ {
/* */     // Move 3 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 24) & 0xFF);
/* */ }
/* */ 
/* */ // Get the green channel.
/* */ static int get_g(int rgba)
/* */ {
/* */     // Move 2 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 16) & 0xFF);
/* */ }
/* */ 
/* */ // Get the blue channel.
/* */ static int get_b(int rgba)
/* */ {
/* */     // Move 1 byte to the right and mask out the first byte.
/* */     return ((rgba >> 8) & 0xFF);
/* */ }
/* */ 
/* */ // Get the alpha channel.
/* */ static int get_a(int rgba)
/* */ {
/* */     // Move 0 bytes to the right and mask out the first byte.
/* */     return (rgba & 0xFF);
/* */ }
/* */ static void	print_tex(t_texture *tmp)
/* */ {
/* */ 	printf(
/* */ 	"[%p] {\n"
/* */ 	"       type          :  {\n"
/* */ 	"                          UNDEFINED     [%d]\n"
/* */ 	"                          VALID         [%d]\n"
/* */ 	"                          COLOR         [%d]\n"
/* */ 	"                          IMAGE         [%d]\n"
/* */ 	"                          SKYBOX        [%d]\n"
/* */ 	"                          ALLOW_CLIP    [%d]\n"
/* */ 	"                          TRANSPARENCY  [%d]\n"
/* */ 	"                        },\n"
/* */ 	"       token         :  \'%c\',\n"
/* */ 	"       *path         :  \"%.15s\",\n"
/* */ 	"       *image        :  [%p],\n"
/* */ 	"       sky_box_token :  \'%c\',\n"
/* */ 	"       *skybox_tex   :  [%p],\n"
/* */ 	"       color         :  [%d, %d, %d, %d]\n"
/* */ 	"     }\n",
/* */ 	(tmp),
/* */ 
/* */ 	(tmp->type & UNDEFINED) != 0,
/* */ 	(tmp->type & VALID) != 0,
/* */ 	(tmp->type & COLOR) != 0,
/* */ 	(tmp->type & IMAGE) != 0,
/* */ 	(tmp->type & SKYBOX) != 0,
/* */ 	(tmp->type & ALLOW_CLIP) != 0,
/* */ 	(tmp->type & TRANSPARENCY) != 0,
/* */ 	
/* */ 	tmp->token,
/* */ 	tmp->path,
/* */ 	tmp->image,
/* */ 
/* */ 	
/* */ 	tmp->sky_box_token,
/* */ 	tmp->skybox_tex,
/* */ 
/* */ 	get_r(tmp->color),
/* */ 	get_g(tmp->color),
/* */ 	get_b(tmp->color),
/* */ 	get_a(tmp->color));
/* */ }
/******************************************************************************/

int	init_map(t_parser *data)
{
	int		err;
	t_chunk	*chunk;

	data->index = 0;
	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_width * data->map_height)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	data->map.len = data->map_width * data->map_height;
	for (uint32_t y = 0; y < data->map_height; y++)
	{
		for (uint32_t x = 0; x < data->map_width; x++)
		{
			chunk = get_chunk_pars(data, set_i32(x, y));
			err = get_next_chunk(data, chunk);
			if (err == EXIT_FAILURE)
				return (ret_print(EXIT_FAILURE, "//TODO"));
			chunk->coord = set_i32(x, y);
			printf("[%d][%d]\n",x, y);
			if (chunk->east)
				print_tex(chunk->east);
			if (err == END_OF_MAP)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}

/*
void	t_map_debug(t_parser *data)
{
	const int	max = data->width * data->height;
	int			index;
	t_coord_i32	coor;
	t_chunk	*tmp;

	index = 0;
	struct_set(&coor, sizeof(coor));
	while (index < max)
	{
		if (coor.x >= data->width)
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
	// t_map_debug(data);//TODO REMOVE
	
	// printf("{{\n%s\n}}\n", data->cube_map);
	// printf("map size [%dx%d]\n", data->width, data->height);
	return (EXIT_SUCCESS);
}
