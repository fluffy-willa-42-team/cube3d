/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:34:26 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/30 15:37:11 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/**
 * @brief Set a chunk floor for the `' '` case.
 *        Set all floor character to `' '`.
 * 
 * @param data Parser struct
 * @param c `.cub` character
 * @return int Return zero value, if there is a error return non zero value.
 */
int	f_123_space(t_parser *data, char c)
{
	if (push_chunk_part(data, c, c, c))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ADD));
	return (EXIT_SUCCESS);
}