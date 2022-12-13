
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
int		test_faild = 0;

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
	char	file[1000] = "./tester/log/";
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

	init_file();
	
	fd_init();

	int run_ret = run(file);

	reset_file();
	printf(BLU"Test [%d]: %s\n"RES, test_no, comm);

	if (run_ret == ret)
		printf(GRE"    OK ([%d])"RES" [%s]\n", run_ret, file);
	else
	{
		test_faild++;
		printf(RED"    K0! ([%d] vs %d)"RES" [%s]\n", run_ret, ret, file);
		printf(BLK"        ./cube3d tester/map/%s\n"RES, file);
	}
	printf("        ["BYEL"./tester/log/%d.out"RES"] ["YEL"./tester/log/%d.err"RES"]\n\n", test_no, test_no);
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	TEST_PRINT("GOOD CUB FILE SEP AND NEWLINE")

	test(	"/good_cub/no_sep_no_newline.cub",
		EXIT_SUCCESS,
		"Good cub file, no tex map separation, no newline at the end.");

	test(	"/good_cub/sep_no_newline.cub",
		EXIT_SUCCESS,
		"Good cub file, tex map separation, no newline at the end.");

	test(	"/good_cub/sep_newline.cub",
		EXIT_SUCCESS,
		"Good cub file, tex map separation, newline at the end.");

	test(	"/good_cub/no_sep_newline.cub",
		EXIT_SUCCESS,
		"Good cub file, no tex map separation, newline at the end.");

	test(	"/good_cub/tex_newline_no_sep_no_newline.cub",
		EXIT_SUCCESS,
		"Good cub file, newline between tex, no tex map separation, no newline at the end.");


	TEST_PRINT("GOOD CUB FILE PLAYER TEST")


	test(	"/good_cub/tex_newline_sep_newline_player_n.cub",
		EXIT_SUCCESS,
		"Good cub file, newline between tex, tex map separation, newline at the end, player set to North");

	test(	"/good_cub/tex_newline_sep_newline_player_s.cub",
		EXIT_SUCCESS,
		"Good cub file, newline between tex, tex map separation, newline at the end, player set to South");

	test(	"/good_cub/tex_newline_sep_newline_player_e.cub",
		EXIT_SUCCESS,
		"Good cub file, newline between tex, tex map separation, newline at the end, player set to East");

	test(	"/good_cub/tex_newline_sep_newline_player_w.cub",
		EXIT_SUCCESS,
		"Good cub file, newline between tex, tex map separation, newline at the end, player set to West");


	TEST_PRINT("BAD CUB FILE PLAYER TEST")


	test(	"/bad_cub/missing_player.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, player missing");

	test(	"/bad_cub/dup_player_w_w.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_n_w.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_s_s.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_n_s.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_n_e.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_w_n.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_s_n.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_s_w.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_e_n.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_w_e.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_e_e.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_w_s.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_e_w.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_s_e.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_n_n.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");

	test(	"/bad_cub/dup_player_e_s.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, duplicate player");



	TEST_PRINT("BAD CUB FILE TEXTURE TEST")


	test(	"/bad_cub/missing_tex_no.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex NO missing");

	test(	"/bad_cub/missing_tex_so.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex SO missing");

	test(	"/bad_cub/missing_tex_we.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex WE missing");

	test(	"/bad_cub/missing_tex_ea.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex EA missing");

	test(	"/bad_cub/missing_tex_f.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex F missing");

	test(	"/bad_cub/missing_tex_c.cub",
		EXIT_FAILURE,
		"Bad cub file, newline between tex, tex map separation, no newline at the end, tex C missing");


	close(fd_out);
	close(fd_err);

	if (test_faild)
		printf(	RED
				"  --===#############################===--  \n"
				"----===### [%d] TESTUNIT FAILD ! ###===----\n"
				"  --===#############################===--  "RES"\n", test_faild);
	else
		printf(	GRE
				"  --===######################===--  \n"
				"----===### TESTUNIT OK :) ###===----\n"
				"  --===######################===--  "RES"\n");

	return 0;
}



