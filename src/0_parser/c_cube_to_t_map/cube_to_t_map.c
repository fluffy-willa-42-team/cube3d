/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/10 16:10:23 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

#include "cube3d_utils.h"

/**
 * TODO
 * 
 * Parse tex and store
 *     - [x] Store in tex_array
 *     - [ ] Check for dup
 *     - [ ] Open tex file
 * Parse map and find HxW
 * 
 * Alloc array map
 * 
 * Init array map
 *     - [ ] Make a function that find chunk with x,y and init a struct in data.
 *           read_chunk(t_data *data.(tmp_)chunk_struct, int x, int y)
 *           t_chunk_struct {TOP,BOTTOM,N,S,E,W,C,F,ENTITY,TAG,...}
 * 
 */


//TODO REMOVE
/******************************************************************************/
/* */ // Get the red channel.
/* */ int get_r(int rgba)
/* */ {
/* */     // Move 3 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 24) & 0xFF);
/* */ }
/* */ 
/* */ // Get the green channel.
/* */ int get_g(int rgba)
/* */ {
/* */     // Move 2 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 16) & 0xFF);
/* */ }
/* */ 
/* */ // Get the blue channel.
/* */ int get_b(int rgba)
/* */ {
/* */     // Move 1 byte to the right and mask out the first byte.
/* */     return ((rgba >> 8) & 0xFF);
/* */ }
/* */ 
/* */ // Get the alpha channel.
/* */ int get_a(int rgba)
/* */ {
/* */     // Move 0 bytes to the right and mask out the first byte.
/* */     return (rgba & 0xFF);
/* */ }
/******************************************************************************/

int	tex_debug(t_parser *data)
{
	int tmp = 0;
	for (int i = '!'; i < 125; i++)
	{
		tmp = get_tex_ptr(&data->tex_list, i)->type;
		if (tmp > 0)
			printf("[%c] {\n    type :   %d,\n    token :  \'%c\',\n    *path :  \"%.10s\",\n    *image : [%p],\n    color :  [%d, %d, %d, %d]\n    }\n", (char)i, get_tex_ptr(&data->tex_list, i)->type, get_tex_ptr(&data->tex_list, i)->token, get_tex_ptr(&data->tex_list, i)->path, get_tex_ptr(&data->tex_list, i)->image, get_r(get_tex_ptr(&data->tex_list, i)->color), get_g(get_tex_ptr(&data->tex_list, i)->color), get_b(get_tex_ptr(&data->tex_list, i)->color), get_a(get_tex_ptr(&data->tex_list, i)->color));
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Return the current character pointed by the index `data->index`.
 * 
 * @warning The function dont check if the `data->index` is out of the memory
 *          scope !
 * 
 * @param data Parser structure.
 */
char	mapchar(t_parser *data)
{
	return (data->cube_map[data->index]);
}

/**
 * @brief Return the current addess pointed by the index `data->index`.
 * 
 * @warning The function dont check if the `data->index` is out of the memory
 *          scope !
 * 
 * @param data Parser structure.
 */
char	*mapptr(t_parser *data)
{
	return (&data->cube_map[data->index]);
}

/**
 * @brief Get the width of the current line.
 *        We consider `width`, all the `' '` only if there is at the beginning
 *        of the line and all non `' '` character.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	get_line_width(t_parser *data)
{
	int	tmp;

	tmp = data->index;
	while (mapchar(data) == ' ')
		data->index++;
	while (mapchar(data) && mapchar(data) != ' ' && mapchar(data) != '\n')
		data->index++;
	tmp = data->index - tmp;
	while (mapchar(data) && mapchar(data) != '\n')
		data->index++;
	if (mapchar(data) == '\n')
		data->index++;
	return (tmp);
}

/**
 * @brief Get the width of the current chunk line.
 *        Check each three line of a chunk line. If the three line dont have the
 *        same width return a error.
 *        We check three line by three, each line need to have the same `width`
 *        (a chunk is 3x3).
 *        We consider `chunk_width`, all the `' '` only if there is at the
 *        beginning of the line and all non `' '` character.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	get_chunk_line_width(t_parser *data)
{
	const int	first_chunk_width = get_line_width(data);
	int			chunk_heigth;
	int			chunk_width;

	chunk_heigth = 1;
	chunk_width = 0;
	while (mapchar(data) && chunk_heigth < 3)
	{
		chunk_width = get_line_width(data);
		if (first_chunk_width != chunk_width)
			return (ret_print(-1, "err no same width"));
		chunk_heigth++;
	}
	if (chunk_heigth == 3)
		return (first_chunk_width);
	return (ret_print(-1, "err chunk no 3 floor"));
}

/**
 * @brief Check if the size of each chunk line is correct and set
 *        `data.map_size.{x, y}`.
 *
 *        We use mapchar() and mapptr() to get the current index char or ptr
 *        from the map. Is the equivalent of `data->cube_map[data->index]`.
 *        To increment the index we set `data->index`.
 * 
 *        We check three line by three, each line need to have the same `width`
 *        (a chunk is 3x3).
 *        We consider `chunk_width`, all the `' '` only if there is at the
 *        beginning of the line and all non `' '` character.
 *        We check if `width` modulo 3 goes not give remainder.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	set_map_size(t_parser *data)
{
	int	biggest_width;
	int	width;
	int	heigth;

	biggest_width = 0;
	width = 0;
	heigth = 0;
	while (mapchar(data))
	{
		width = get_chunk_line_width(data);
		if (width == -1)
			return (EXIT_FAILURE);
		if (width%3)
			return (ret_print(EXIT_FAILURE, "err bad chunk width"));
		if (width > biggest_width)
			biggest_width = width;
		heigth++;
	}
	data->map_size.x = biggest_width;
	data->map_size.y = heigth;
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
	printf(
		"{{\n%s\n}}\n",
		mapptr(data)
	);
	if (set_map_size(data))
		return (EXIT_FAILURE);
	printf(
		"map size [%dx%d]\n",
		data->map_size.x,
		data->map_size.y
	);
	return (EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @param data Parser structure.
 * @return int 
 */
int	cube_to_t_map(t_parser *data)
{
	if (store_texture(data, data->cube.buffer) /*TODO REMOVE*/|| tex_debug(data)/*TODO REMOVE*/
		|| store_map(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}