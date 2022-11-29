/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sani.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 09:24:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "vector_lib.h"

/* ret_print */
#include "cube3d_debug.h"

/* memmove */
#include "lib_mem.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* ft_strlen */
#include "lib_str.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check if the `c` char is in the `set` char array.
 * 
 * @param set The char array
 * @param c The char to check
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
static int	charset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Remove leading and trailing whitespace from the buffer.
 * 
 * @param buff Buffer to trim
 * @return int Return zero value, if there is an error return non zero value.
 */
static int	bufftrim(t_vec *buff)
{
	char	*str;
	int		trim;
	int		len;

	trim = 0;
	str = (char *)buff->buffer;
	while (str[trim] && charset(WHITE_SPACE, str[trim]))
		trim++;
	len = ft_strlen(&str[trim]);
	if (trim)
	{
		ft_memmove(str, &str[trim], len);
		str[len] = '\0';
	}
	len--;
	while (len >= 0 && charset(WHITE_SPACE, str[len]))
	{
		str[len] = '\0';
		len--;
	}
	buff->len = ft_strlen(str);
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief If there is other withe space
 *        than `' '` and `'\n'` will return a error.
 * 
 * @param buff The buffer to clean
 * @return int Return zero value, if there is an error return non zero value.
 */
static int	sanitize_white_space(t_vec *buff)
{
	int	i;

	i = 0;
	while (((char *)buff->buffer)[i])
	{
		if (charset(UNAUTHORIZED_SPACE, ((char *)buff->buffer)[i]))
			return (ret_print(EXIT_FAILURE, ERR_SANI_FILE));
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Remove the trailing witespace and check if all white space are space
 *        `' '`.
 */
int	file_sani(t_parser *data)
{
	t_vec	*buff;

	if (data->type == CUB_FILE)
		buff = &data->cub;
	else if (data->type == CUBE_FILE)
		buff = &data->cube;
	else
		return (ret_print(EXIT_FAILURE, ERR_RFILE_TYPE));
	if (sanitize_white_space(buff) || bufftrim(buff))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
