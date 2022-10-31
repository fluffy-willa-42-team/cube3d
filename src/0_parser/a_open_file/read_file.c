/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/31 12:04:04 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* v_readline */
#include "vector_lib.h"

/* ret_print */
#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

/**
 * @brief Read file and wirte in the `buff`.
 * 
 * @param data Parser structure
 * @param buff The buffer to write the file
 * @return int Return zero value, if there is an error return non zero value.
 */
static int	read_to_vec(t_parser *data, t_vec *buff)
{
	int	ret;
	int	len;

	len = 0;
	ret = 1;
	*buff = v_init_r(sizeof(char), NULL, NULL, 1000000);
	if (!v_alloc(buff, SET, 5000000))// TODO check for opti
		return(ret_print(EXIT_FAILURE, "//TODO FAIL v_alloc"));
	while (ret != 0)
	{
		ret = v_readline(buff, data->file_fd);
		len += ret;
		if (ret == -1 || !v_add(buff, STRING, "\n")/* //TODO change check after the lib update ! */)
			return (ret_print(EXIT_FAILURE, ERR_RDL_FAIL));
	}
	if (!len)
		return (ret_print(EXIT_FAILURE, ERR_EMPTY_FILE));
	return (EXIT_SUCCESS);
}

/**
 * @author Matthew-Dreemurr
 * 
 * @brief Read the file and store in `data->cube, if is a `.cub` will  read in
 *        `data->cub` and convert to `.cube` format in `data->cube`.
 * 
 * @param data Parser structure
 * @return int Return zero value, if there is an error return non zero value.
 */
int	read_file(t_parser *data)
{
	int	err;

	err = 0;
	if (data->type == CUB_FILE)
		err = read_to_vec(data, &data->cub);
	else if (data->type == CUBE_FILE)
		err = read_to_vec(data, &data->cube);
	else
		return (ret_print(EXIT_FAILURE, ERR_RFILE_TYPE));
	if (err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
