
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define RED "\033[0;31m"
#define GRE "\033[0;32m"
#define YEL "\033[0;33m"
#define BYEL "\e[1;33m"
#define YELHB "\e[0;103m"
#define RES "\033[0m"
#define BLK "\e[0;30m"
#define BLU "\e[0;34m"

#define TEST_PRINT(x) printf(RED"\n-------=====$$[%s]$$=====-------\n"RES"\n", x);

int		fd_out;
int		fd_err;
int		file_out;
int		file_err;
int		test_no = -1;

/**
 * @brief copy `src` in `dest` starting by the end of `src`
 * 
 * @param dest
 * @param src
 */
static void	rev_cpy(char *dest, const char *src)
{
	const char	*start;

	start = src;
	while (*src)
		src++;
	while (src-- > start)
		*dest++ = *src;
	*dest = '\0';
}

/**
 * index   0  1  2  3  4  5  6  7  8  9  10 11
 *        [8][4][6][3][8][4][7][4][1][2][-][\0]
 * @brief Convert integer to string of char. (use malloc())
 * 
 * @param n The integer to convert.
 * @return  char* The string representing the integer. NULL if the
 *          allocation fails.
 *
 */
char	*ft_itoa(int n)
{
	char	buff[12];
	char	*str;
	size_t	nbr;

	nbr = (unsigned int []){n, -n}[n < 0];
	str = buff;
	if (nbr == 0)
		*str++ = '0';
	while (nbr > 0)
	{
		*str++ = (char)((nbr % 10) + '0');
		nbr /= 10;
	}
	*str++ = (char []){'\0', '-'}[n < 0];
	*str = '\0';
	str = (char *)malloc(sizeof(char) * strlen(buff) + 1);
	if (!str)
		return (NULL);
	rev_cpy(str, buff);
	return (str);
}

int	create_file(const char *ext)
{
	char	file[1000] = "./tester/";
	int		fd;
	char	*file_name = ft_itoa(test_no);

	if (!file_name) {perror("itoa fail !\n");exit (EXIT_FAILURE);}
	strcat(file, file_name);
	strcat(file, ext);
	free(file_name);
	if ((fd = open(file, O_RDWR|O_CREAT, 0600)) == -1)
	{
		perror("Fail to create file ");
		perror(file);
		perror("\n");
		exit (EXIT_FAILURE);
	}
	return (fd);
}

void	init_file()
{
	file_out = create_file(".out");
	file_err = create_file(".err");
}

void	fd_init()
{
	if ((fd_out = dup(fileno(stdout)) == -1))
	{
		perror("Fail dup stdout !\n");
		exit (EXIT_FAILURE);
	}
	if ((fd_err = dup(fileno(stderr)) == -1))
	{
		perror("Fail dup stderr !\n");
		exit (EXIT_FAILURE);
	}
	if (-1 == dup2(file_out, fileno(stdout)))
	{
		perror("Fail to dup2 stdout !\n");
		exit (EXIT_FAILURE);
	}
	if (-1 == dup2(file_err, fileno(stderr)))
	{
		perror("Fail to dup2 stdout !\n");
		exit (EXIT_FAILURE);
	}

}

void	reset_file()
{
	fflush(stdout); close(file_out);
	fflush(stderr); close(file_err);

	dup2(fd_out, fileno(stdout));
	dup2(fd_err, fileno(stderr));
}

int	run(const char *file)
{
	pid_t p;
	int stat;

	char buff[1000] = "tester/map/";
	strcat(buff, file);

	/* split this program into two processes */
	p = fork();

	if( p == 0 ) /* child process is running */
	{
		execl("cube3d", "cube3d", buff, (char *)0);
	}
	else /* parent process is running */
	{
		wait(&stat); /* wait for the child */
		return (WEXITSTATUS(stat));
	}
	return(-255);
}

void	test(const char *file, int ret, const char *comm)
{
	test_no++;

	init_file(file);
	
	fd_init();

	int run_ret = run(file);

	reset_file();
	printf(BLU"Test [%d]: %s\n"RES, test_no, comm);

	if (run_ret == ret)
		printf(GRE"    OK ([%d])"RES" [%s]\n", run_ret, file);
	else
	{
		printf(RED"    K0! ([%d] vs %d)"RES" [%s]\n", run_ret, ret, file);
		printf(BLK"        ./cube3d tester/map/%s\n"RES, file);
	}
	printf("        ["BYEL"./tester/%d.out"RES"] ["YEL"./tester/%d.err"RES"]\n\n", test_no, test_no);
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	TEST_PRINT("BASIC FILE TEST")
	
	test(	"cub_map.cub",
			EXIT_SUCCESS,
			"Normal cub file");

	test(	"cube_map.cube",
			EXIT_SUCCESS,
			"Normal cube file");

	test(	"cub_map.cube",
			EXIT_FAILURE,
			".cube file with a .cub map format");

	test(	"empty_file.cub",
			EXIT_FAILURE,
			"Empty file .cub");

	test(	"empty_file.cube",
			EXIT_FAILURE,
			"Empty file .cube");

	test(	"cub_no_rwx_perm.cub",
			EXIT_FAILURE,
			".cub file -rwx");

	test(	"cub_no_rwx_perm.cube",
			EXIT_FAILURE,
			".cube file -rwx");

	test(	"no_rwx_perm",
			EXIT_FAILURE,
			"Empty file no extention -rwx");

	TEST_PRINT("PLAYER TEST")

	test(	"cub_player_W.cub",
			EXIT_SUCCESS,
			"Good cub file with player to W");

	test(	"cub_player_S.cub",
			EXIT_SUCCESS,
			"Good cub file with player to S");

	test(	"cub_player_E.cub",
			EXIT_SUCCESS,
			"Good cub file with player to E");

	test(	"cub_player_N.cub",
			EXIT_SUCCESS,
			"Good cub file with player to N");

	test(	"cub_player_none.cub",
			EXIT_FAILURE,
			"Good cub file without player");

	TEST_PRINT("TEXTURE TEST")

	test(	"cub_tex_without_F.cub",
		EXIT_FAILURE,
		"Good cub file without F texture");

	test(	"cub_tex_without_C.cub",
		EXIT_FAILURE,
		"Good cub file without C texture");

	test(	"cub_tex_without_NO.cub",
		EXIT_FAILURE,
		"Good cub file without NO texture");

	test(	"cub_tex_without_SO.cub",
		EXIT_FAILURE,
		"Good cub file without SO texture");

	test(	"cub_tex_without_WE.cub",
		EXIT_FAILURE,
		"Good cub file without WE texture");

	test(	"cub_tex_without_EA.cub",
		EXIT_FAILURE,
		"Good cub file without EA texture");

	test(	"cub_tex_dup_NO.cub",
		EXIT_FAILURE,
		"Good cub file with duplication NO texture");

	test(	"cub_tex_dup_SO.cub",
		EXIT_FAILURE,
		"Good cub file with duplication SO texture");

	test(	"cub_tex_dup_EA.cub",
		EXIT_FAILURE,
		"Good cub file with duplication EA texture");

	test(	"cub_tex_dup_WE.cub",
		EXIT_FAILURE,
		"Good cub file with duplication WE texture");

	test(	"cub_tex_dup_C.cub",
		EXIT_FAILURE,
		"Good cub file with duplication C texture");

	test(	"cub_tex_dup_F.cub",
		EXIT_FAILURE,
		"Good cub file with duplication F texture");

	close(fd_out);
	close(fd_err);
	return 0;
}