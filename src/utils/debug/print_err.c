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
	int fd;

	fd = STDOUT_FILENO + (ret != EXIT_SUCCESS);
	if (msg)
		write(fd, msg, ft_strlen(msg));
	return (ret);
}