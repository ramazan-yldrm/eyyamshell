#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int fd1 = open("file1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

	printf("fd1: %d, fd2: %d\n", fd1, fd2);
	write(fd2, "Hello, World!\n", 14);
}
