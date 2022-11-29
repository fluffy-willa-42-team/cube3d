/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_t_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:47:45 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/29 13:50:52 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"
/* close() */
#include <unistd.h>

/* free() */
#include <stdlib.h>

/* strerror() */
#include <string.h>

/* perror() */
#include <stdio.h>

/* errno */
#include <errno.h>

/* v_delete() */
#include "vector_lib.h"

/* ft_strlen() */
#include "lib_str.h"

/**
 * @brief Check if the `fd` is successfully close, otherwise print a error
 *        message.
 * 
 * @note man: Linux 2019-10-10 CLOSE(2)
 * Dealing with error returns from close()
 *   A careful programmer will check the return value of close(),  since  it  is
 *   quite  possible  that  errors on a previous write(2) operation are reported
 *   only on the final close() that releases the open file description.
 * 
 *   Note, however, that a failure return should be  used  only  for  diagnostic
 *   purposes  (i.e.,  a  warning to the application that there may still be I/O
 *   pending or there may have been failed  I/O)  or  remedial  purposes  (e.g.,
 *   writing the file once more or creating a backup).
 * 
 * @param fd The fd to close
 * 
 * @return int `0` if the fd is closed, `1` if `close()` fail.
 * 
 */
int	close_check(int fd)
{
	const char	*err = "Error\n";
	const int	ret = close(fd);

	if (ret == 0)
		return (EXIT_SUCCESS);
	write(fd, err, ft_strlen(err));
	write(fd, strerror(errno), ft_strlen(strerror(errno)));
	write(fd, "\n", 1);
	return (EXIT_FAILURE);
}


static int	close_config_file(t_parser *data)
{
	return (close_check(data->file_fd));
}

// static int	destroy_vec(t_vec *vector)
// {
// 	v_delete(vector);
// 	return (EXIT_FAILURE);
// }

static int	free_all_vec(t_parser *data)
{
	(void) data;
	return (EXIT_SUCCESS);
}

int	destroy_t_parser(t_parser *data)
{
	return (close_config_file(data)
		|| free_all_vec(data)
		|| struct_set(data, sizeof(t_parser)));
}

