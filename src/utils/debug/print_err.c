/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:55:28 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/21 11:58:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_strlen() */
#include "lib_str.h"

/* write() */
#include <unistd.h>

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "cube3d_debug.h"

/**
 * @brief Print `msg` and return `ret` value.
 * 
 * @param ret Value to return
 * @param msg String to print on the stderr
 * @return int `ret`
 */
int	ret_print(int ret, const char *msg)
{
	int	fd;

	fd = STDOUT_FILENO + (ret != EXIT_SUCCESS);
	if (!msg)
		return (ret);
	write(fd, ERR_PREFIX, ft_strlen(ERR_PREFIX));
	write(fd, msg, ft_strlen(msg));
	write(fd, ERR_SUFFIX, ft_strlen(ERR_SUFFIX));
	return (ret);
}
