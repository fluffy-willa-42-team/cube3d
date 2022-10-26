/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:50:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/26 16:05:18 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* open() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* ft_strlen() */
#include "lib_str.h"

/**
 * @author Matthew-Dreemurr
 * 
 * @brief Check if the `path` file extension is the same as `ext`.
 *
 * @param path The path string
 * @param ext The extesion string
 * @return int If the file have the rigth extension will return zero else
 *             non zero value.
 */
static int	extcmp(char *path, const char *ext)
{
	char	*tmp;
	size_t	path_len;
	size_t	ext_len;

	if (!path || !ext)
		return (EXIT_FAILURE);
	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (ext_len > path_len)
		return (EXIT_FAILURE);
	tmp = path;
	tmp += path_len - ext_len;
	return (ft_strcmp(tmp, ext));
}

/**
 * @author Matthew-Dreemurr
 * 
 * @brief Check if the file in path have `.cub` or `.cube` extension.
 *        Will set `data.type` with the macro `CUB_FILE` or `CUBE_FILE`.
 *
 * @param data Parser structure
 * @return int Return zero value if the extesion is correcte, if not return
 *             non zero value.
 */
static int	check_extension(t_parser *data)
{
	if (!extcmp(data->path, ".cub"))
		data->type = CUB_FILE;
	else if (!extcmp(data->path, ".cube"))
		data->type = CUBE_FILE;
	else
		return (ret_print(EXIT_FAILURE, ERR_FILE_EXT));
	return (EXIT_SUCCESS);
}

/**
 * @author Matthew-Dreemurr
 *
 * @brief Open file and set the fd in `data->file_fd`.
 * 
 * @param data Parser structure
 * @return int Return zero value if the file is open, if not return
 *             non zero value.
 */
static int	open_fd(t_parser *data)
{
	data->file_fd = open(data->path, O_RDONLY);
	if (data->file_fd == -1)
		return (ret_print(EXIT_FAILURE, ERR_OPEN_FILE));
	return (EXIT_SUCCESS);
}

/**
 * @author Matthew-Dreemurr
 *
 *  @brief Check extention and open file. Set `data->file_fd` with the file fd.
 * 
 * @param data Parser structure
 * @return int Return zero value if the file is open, if not return
 *             non zero value.
 */
int	open_file(t_parser *data)
{
	if (check_extension(data) || open_fd(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
