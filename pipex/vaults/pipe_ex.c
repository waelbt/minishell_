# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>



int main(int argc , char **argv)
{
	int fd[2];
	
	fd[0] = open("txt.txt", O_RDONLY);
	fd[1] = open("txt.txt", O_WRONLY);

	int id = fork();
	if(id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number:  ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		sleep(3);
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got form child process %d\n", y);
	}
	return (0);
}