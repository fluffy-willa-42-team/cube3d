/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/01 16:22:52 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

int	cube_to_t_map(t_parser *data)
{
	//Parse tex and store
	//    - [ ] Store in array
	//    - [ ] Check for dup
	//    - [ ] Open tex file

	//Parse map and find HxW

	//Alloc array map

	//Init array map
	//    - [ ] Make a function that find chunk with x,y and init a struct in data.
	//          read_chunk(t_data *data.(tmp_)chunk_struct, int x, int y)
	//          t_chunk_struct {TOP,BOTTOM,N,S,E,W,C,F,ENTITY,TAG,...}
	return (EXIT_SUCCESS);
}