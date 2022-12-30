/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:55:28 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/30 12:59:01 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_strlen() */
#include "lib_str.h"

/* write() */
#include <unistd.h>

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

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
	write(fd, "\n\e[0;31mError\n", ft_strlen("\n\e[0;31mError\n"));
	write(fd, msg, ft_strlen(msg));
	write(fd, "\n\e[0m", ft_strlen("\n\e[0m"));
	return (ret);
}
