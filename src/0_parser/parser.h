#ifndef PARSER_H
# define PARSER_H

# include "vector_lib.h"

# define CUB_FILE 1
# define CUBE_FILE 2

/**
 * @param type     (int)    Type of the file `.cub` or `.cube`
 * @param file_fd  (int)    Fd of the file
 * @param *path    (char)   Path file from the main
 * @param cub     (t_vec)   Buffer to write the `.cub`  file
 * @param cube    (t_vec)   Buffer to write the `.cube` file
 */
typedef struct s_parser
{
	int		type;
	int		file_fd;
	char	*path;
	t_vec	cub;
	t_vec	cube;
}				t_parser;

int parser(char *av);
int	open_file(t_parser *data);
int	read_file(t_parser *data);
int	file_sani(t_parser *data);
int	file_conv(t_parser *data);

#endif /* PARSER_H */
