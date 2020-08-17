#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define	BUFF_SIZE	100

void	error_handling(char *s)
{
	fputs(s, stderr);
	fputc('\n', stderr);
	exit(1);
}



int		main(void)
{
	char	buff[BUFF_SIZE];
	int		fd;

	fd = open ("data.txt", O_RDONLY);

	if (fd == -1)
		error_handling("open error!\n");
	printf("file descriptor : %d\n", fd);
	if (read(fd, buff, sizeof(buff)) == -1)
		error_handling("read error!\n");
	printf("file data : %s\n", buff);
	close(fd);
}