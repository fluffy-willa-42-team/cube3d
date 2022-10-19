

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
 * @brief Check if the `path` file extension is the same as `ext`.
 *
 * @param path The path string
 * @param ext The extesion string
 * @return int If the file have the rigth extension will return zero else
 *             non zero value.
 */
static int extcmp(char *path, const char *ext)
{
	char *tmp;
	size_t path_len;
	size_t ext_len;

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
 * @brief Check if the file in path have `.cub` or `.cube` extension.
 *        Will set `data.type` with the macro `CUB_FILE` or `CUBE_FILE`
 *
 * @param path File path string
 * @param data Parser structure
 * @return int Return zero value if the extesion is correcte, if not return
 *             non zero value.
 */
static int check_extension(char *path, t_parser *data)
{
	if (!extcmp(path, ".cub"))
		data->type = CUB_FILE;
	else if (!extcmp(path, ".cube"))
		data->type = CUBE_FILE;
	else
		return (ret_print(EXIT_FAILURE, ERR_FILE_EXT));
	return (EXIT_SUCCESS);
}

static int open_file(t_parser *data)
{
	(void)data;
	write(STDOUT_FILENO, "READ FILE\n", 11);
	return (EXIT_SUCCESS);
}

int parser(char *av)
{
	t_parser data;

	struct_set(&data, sizeof(data));
	if (check_extension(av, &data) || open_file(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}