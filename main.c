#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void test1(int argc, char **argv)
{
	int	fd1;
	char	*line;
	int	ret;

	printf("\nRunning test1...\n\nReading simple testfile with 5 lines and printing return values from every call:\n");
	ret = 1;
	(void) argc;
	fd1 = open(argv[1], O_RDONLY);
	if (argc > 1)
	{
		while (ret)
		//for (int i = 0; i < 10; i++)
		{
			ret = get_next_line(fd1, &line);
			printf("%d '%s'\n", ret, line);
			ft_strdel(&line);
		}
		close(fd1);
	}
}

void test2()
{
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;
	char *line;

	out = dup(1);
	pipe(p);

	printf("\nRunning test2...\n\nReading from string with two newlines in the end:\n");
	fd = 1;
	dup2(p[1], fd);
	write(fd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, fd);
	gnl_ret = get_next_line(p[0], &line);
	printf("%d '%s'\n", gnl_ret, line);
	gnl_ret = get_next_line(p[0], &line);
	printf("%d '%s'\n", gnl_ret, line);
	gnl_ret = get_next_line(p[0], &line);
	printf("%d '%s'\n", gnl_ret, line);
	gnl_ret = get_next_line(p[0], &line);
	printf("%d '%s'\n", gnl_ret, line);
}

void	test3()
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		gnl_ret;

	printf("\nRunning test3...\n\nReading long string without newlines. Return value should be 1 and strcmp with the original string should return 0:\n");
	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);

	write(1, str, strlen(str));
	close(p[1]);
	dup2(out, 1);
	gnl_ret = get_next_line(p[0], &line);
	printf("After calling once return value is %d, strcmp returns %d\n", gnl_ret, strcmp(line, str));
	//printf("\n---\n%s\n---\n%s\n---\n", line, str);
}

void	test4()
{
	char 	*line = NULL;
   
    printf("\nRunning test4...\n\nTrying negative or non-opened file descriptors, should be all -1:\n");	
	printf("%d\n", get_next_line(-99, NULL));
	printf("%d\n", get_next_line(-1, NULL));
	printf("%d\n", get_next_line(-10000, NULL));
	printf("%d\n", get_next_line(-1, NULL));
	printf("%d\n", get_next_line(-99, NULL));
	printf("%d\n", get_next_line(-99, &line));
	printf("%d\n", get_next_line(-1, &line));
	printf("%d\n", get_next_line(-10000, &line));
	printf("%d\n", get_next_line(42, &line));
}
	
void	test5()
{
	char	*line_fd0;
	int		p_fd0[2];
	int		fd0 = 0;
	int		out_fd0 = dup(fd0);

	char	*line_fd1;
	int		p_fd1[2];
	int		fd1 = 1;
	int		out_fd1 = dup(fd1);

	char	*line_fd2;
	int		p_fd2[2];
	int		fd2 = 2;
	int		out_fd2 = dup(fd2);

	char	*line_fd3;
	int		p_fd3[2];
	int		fd3 = 3;
	int		out_fd3 = dup(fd3);

	printf("\nRunning test5 (bonus)...\n\nTrying to read from different file descriptors, strcmp should return 0 everywhere:\n");
	pipe(p_fd0);
	dup2(p_fd0[1], fd0);
	write(fd0, "aaa\nbbb\n", 8);
	dup2(out_fd0, fd0);
	close(p_fd0[1]);

	pipe(p_fd1);
	dup2(p_fd1[1], fd1);
	write(fd1, "111\n222\n", 8);
	dup2(out_fd1, fd1);
	close(p_fd1[1]);

	pipe(p_fd2);
	dup2(p_fd2[1], fd2);
	write(fd2, "www\nzzz\n", 8);
	dup2(out_fd2, fd2);
	close(p_fd2[1]);

	pipe(p_fd3);
	dup2(p_fd3[1], fd3);
	write(fd3, "888\n999\n", 8);
	dup2(out_fd3, fd3);
	close(p_fd3[1]);

	get_next_line(p_fd0[0], &line_fd0);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd0, "aaa"), line_fd0);

	get_next_line(p_fd1[0], &line_fd1);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd1, "111"), line_fd1);

	get_next_line(p_fd2[0], &line_fd2);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd2, "www"), line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd3, "888"), line_fd3);
	
	get_next_line(p_fd0[0], &line_fd0);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd0, "bbb"), line_fd0);
	
	get_next_line(p_fd1[0], &line_fd1);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd1, "222"), line_fd1);
	
	get_next_line(p_fd2[0], &line_fd2);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd2, "zzz"), line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd3, "999"), line_fd3);
}

void	test6()
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	char		*filename;
	int			errors;

	filename = "gnl7_1.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		errors = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "12345678") != 0)
				errors++;
			count_lines++;
			printf("%s\n", line);
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 1)
			printf("-> must have returned '1' once instead of %d time(s)\n", count_lines);
		if (errors > 0)
			printf("-> must have read \"12345678\" instead of \"%s\"\n", line);
		if (count_lines == 1 && errors == 0)
			printf("OK\n");
	}
	else
		printf("An error occured while opening file %s\n", filename);
}

/*void	test7()
{
	int  stdout_bk; //is fd for stdout backup

   printf("this is before redirection\n");
   stdout_bk = dup(fileno(stdout));

   int pipefd[2];
   pipe(pipefd, 0); // O_NONBLOCK);

   // What used to be stdout will now go to the pipe.
   dup2(pipefd[1], fileno(stdout));

   printf("this is printed much later!\n");
   fflush(stdout);//flushall();
   write(pipefd[1], "good-bye", 9); // null-terminated string!
   close(pipefd[1]);

   dup2(stdout_bk, fileno(stdout));//restore
   printf("this is now\n");

   char buf[101];
   read(pipefd[0], buf, 100);
   printf("got this from the pipe >>>%s<<<\n", buf);
  }*/

int		main(int argc, char *argv[])
{
	//(void) argc;
	//(void) argv;
	test1(argc, argv);
	test2();
	test3();
	test4();
	test5();
	//test6();
	//test7();
	return (0);
}
