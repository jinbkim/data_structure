#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	error_handling(char *s)
{
	fputs(s, stderr);
	fputc('\n', stderr);
	exit(1);
}



int		main(void)
{
	char	buff[] = "hello world!\n";
	int		fd;

	fd = open ("data.txt", O_WRONLY|O_TRUNC);

	if (fd == -1)
		error_handling("open error!\n");
	printf("file descriptor : %d\n", fd);
	if (write(fd, buff, sizeof(buff)) == -1)
		error_handling("write error!\n");
	close(fd);
}