/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:38:57 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/25 15:49:48 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Get the width of the current line.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	get_line_width(t_parser *data)
{
	int	tmp;

	tmp = data->index;
	while (data->cube_map[tmp] && data->cube_map[tmp] != '\n')
		tmp++;
	return (tmp - data->index);
}
