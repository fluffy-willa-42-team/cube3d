

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

int	file_conv(t_parser *data)
{
	if (data->type == CUB_FILE)
		if (/*conversion()*/0 || !v_delete(&data->cub)/* //TODO change check after the lib update ! */)
			return(ret_print(EXIT_FAILURE, "WIP/n"));//TODO
	return (EXIT_SUCCESS);
}