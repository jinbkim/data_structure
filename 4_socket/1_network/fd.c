#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int		main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;

	fd1 = socket(PF_INET, SOCK_STREAM, 0);
	fd2 = open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
	fd3 = socket(PF_INET, SOCK_STREAM, 0);

	printf("fd1 : %d\n", fd1);
	printf("fd2 : %d\n", fd2);
	printf("fd3 : %d\n", fd3);

	close(fd1);
	close(fd2);
	close(fd3);
}