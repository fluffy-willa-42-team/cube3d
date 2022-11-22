/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_char_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:35:23 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:46:15 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
