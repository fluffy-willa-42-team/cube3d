

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

static int	conversion(t_parser *data)
{
	(void)data;
	return (EXIT_SUCCESS);
}

int	file_conv(t_parser *data)
{
	if (data->type == CUB_FILE)
		if (conversion(data) || !v_delete(&data->cub)/* //TODO change check after the lib update ! */)
			return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}