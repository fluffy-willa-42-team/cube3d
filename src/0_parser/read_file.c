

#include "parser.h"

/* v_readline */
#include "vector_lib.h"

/* ret_print */
#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

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
	write(1, "start read\n", 12);
	ret = 1;
	*buff = v_init(sizeof(char), NULL, NULL);
	v_alloc(buff, SET, 5000000);
	while (ret != 0)
	{
	write(1, "read\n", 6);
		ret = v_readline(buff, data->file_fd);
		if (ret == -1 || !v_add(buff, STRING, "\n")/* //TODO change check after the lib update ! */)
			return (ret_print(EXIT_FAILURE, ERR_VEC_FAIL));
	}
	v_print(buff);//TODO REMOVE
	write(1, "finish\n", 8);
	return (EXIT_SUCCESS);
}

/**
 * @Matthew-Dreemurr
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
		return(ret_print(EXIT_FAILURE, ERR_RFILE_TYPE));
	if (err)
		return (ret_print(EXIT_FAILURE, ERR_READ_TO_VEC));
	return (EXIT_SUCCESS);
}