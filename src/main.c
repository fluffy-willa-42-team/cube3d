
#include "parser.h"

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	if (parser(argv[1]))
		return (1);
	return (0);
}
