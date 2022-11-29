/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:04:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 09:21:44 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the first chunk floor for the `'1'` case.
 *        TOP is set with the ceiling texture index (or `get_tex("C")`).
 *        NORTH is set with the north texture index (or `get_tex("NO")`).
 *        And ENTITY is set to '.' (or E_EMPTY).
 *
 * @details floor 1 : TOP | NORTH | ENTITY

 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_1_one(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("C"), get_tex("NO"), E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the second chunk floor for the `'1'` case.
 *        WEST is set with the west texture index (or `get_tex("WE")`).
 *        EAST is set with the east texture index (or `get_tex("EA")`).
 *        And TEX is set to '.' (or E_EMPTY).
 *
 * @details floor 2 : WEST | EAST | TEX
 * 
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_2_one(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("WE"), get_tex("EA"), E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
 * 
 * @brief Set the last chunk floor for the `'1'` case.
 *        BOTTOM is set with the floor texture index (or `get_tex("F")`).
 *        SOUTH is set with the east texture index (or `get_tex("SO")`).
 *        And OPT is set to '.' (or E_EMPTY).
 *
 * @details floor 3 : BOTTOM | SOUTH | OPT
 *
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_3_one(t_parser *data, char c)
{
	(void)c;
	if (push_chunk_part(data, get_tex("F"), get_tex("SO"), E_EMPTY))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}
