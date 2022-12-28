/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:48:29 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 15:31:23 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* struct_set() */
#include "cube3d_utils.h"

#include <stdio.h>//TODO REMOVE

//TODO REMOVE
/******************************************************************************/
// /* */ // Get the red channel.
// /* */ static int get_r(int rgba)
// /* */ {
// /* */     // Move 3 bytes to the right and mask out the first byte.
// /* */     return ((rgba >> 24) & 0xFF);
// /* */ }
// /* */ 
// /* */ // Get the green channel.
// /* */ static int get_g(int rgba)
// /* */ {
// /* */     // Move 2 bytes to the right and mask out the first byte.
// /* */     return ((rgba >> 16) & 0xFF);
// /* */ }
// /* */ 
// /* */ // Get the blue channel.
// /* */ static int get_b(int rgba)
// /* */ {
// /* */     // Move 1 byte to the right and mask out the first byte.
// /* */     return ((rgba >> 8) & 0xFF);
// /* */ }
// /* */ 
// /* */ // Get the alpha channel.
// /* */ static int get_a(int rgba)
// /* */ {
// /* */     // Move 0 bytes to the right and mask out the first byte.
// /* */     return (rgba & 0xFF);
// /* */ }
// /* */ static void	print_tex(t_texture *tmp)
// /* */ {
// /* */ 	printf(
// /* */ 	"[%p] {\n"
// /* */ 	"       type          :  {\n"
// /* */ 	"                          UNDEFINED     [%d]\n"
// /* */ 	"                          VALID         [%d]\n"
// /* */ 	"                          COLOR         [%d]\n"
// /* */ 	"                          IMAGE         [%d]\n"
// /* */ 	"                          SKYBOX        [%d]\n"
// /* */ 	"                          ALLOW_CLIP    [%d]\n"
// /* */ 	"                          TRANSPARENCY  [%d]\n"
// /* */ 	"                        },\n"
// /* */ 	"       token         :  \'%c\',\n"
// /* */ 	"       *path         :  \"%.15s\",\n"
// /* */ 	"       *image        :  [%p],\n"
// /* */ 	"       token_ptr :  \'%c\',\n"
// /* */ 	"       *skybox_tex   :  [%p],\n"
// /* */ 	"       color         :  [%d, %d, %d, %d]\n"
// /* */ 	"     }\n",
// /* */ 	(tmp),
// /* */ 
// /* */ 	(tmp->type & UNDEFINED) != 0,
// /* */ 	(tmp->type & VALID) != 0,
// /* */ 	(tmp->type & COLOR) != 0,
// /* */ 	(tmp->type & IMAGE) != 0,
// /* */ 	(tmp->type & SKYBOX) != 0,
// /* */ 	(tmp->type & ALLOW_CLIP) != 0,
// /* */ 	(tmp->type & TRANSPARENCY) != 0,
// /* */ 	
// /* */ 	tmp->token,
// /* */ 	tmp->path,
// /* */ 	tmp->image,
// /* */ 
// /* */ 	
// /* */ 	tmp->token_ptr,
// /* */ 	tmp->skybox_tex,
// /* */ 
// /* */ 	get_r(tmp->color),
// /* */ 	get_g(tmp->color),
// /* */ 	get_b(tmp->color),
// /* */ 	get_a(tmp->color));
// /* */ }
/******************************************************************************/

int	init_map_while(t_parser *data)
{
	int32_t		x;
	int32_t		y;
	int			err;
	t_chunk		*chunk;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		err = 0;
		while (x < data->map_width)
		{
			chunk = get_chunk_pars(data, set_i32(x, y));
			chunk->coord = set_i32(x, y);
			if (err == END_OF_LINE || err == END_OF_MAP)
				chunk->type = WHITE_SPACE_CHUNK;
			else
				err = get_next_chunk(data, chunk);
			if (err == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int	init_map(t_parser *data)
{
	data->index = 0;
	data->map = v_init(sizeof(t_chunk), NULL, NULL);
	if (!v_alloc(&data->map, SET, (data->map_width * data->map_height)))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	data->map.len = data->map_width * data->map_height;
	if (init_map_while(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
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
	if (set_map_size(data) || init_map(data) || check_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
