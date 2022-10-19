#ifndef PARSER_H
# define PARSER_H

# include "vector_lib.h"
# include "cube3d_debug.h"

# define CUB_FILE 1
# define CUBE_FILE 2

typedef struct s_parser
{
	int	type;
	int	file_fd;
}				t_parser;

int parser(char *av);

#endif /* PARSER_H */
