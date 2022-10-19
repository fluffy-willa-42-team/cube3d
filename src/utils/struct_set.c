

/* t_parser */
#include "parser.h"

/* ft_memset() */
#include "lib_mem.h"

/**
 * @brief Set all variable the variable to 0
 * 
 * @param var Pointer to the variable
 * @param size Size of the variable
 * @return void* The variable pointer
 */
void	*struct_set(void *var, int size)
{
	return (ft_memset(var, 0, size));
}
