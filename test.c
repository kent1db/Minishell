#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	test()
{
	pid_t pid;
	int fd_p[2];
	int	status;
	int	backup[2];
	int	backup_pipe[2];
	backup[0] = dup(0);
	backup[1] = dup(1);
	pipe(fd_p);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_p[1], 1);
		close(fd_p[0]);
		system("ls");
		exit(0);
	}
	wait(&status);
	backup_pipe[0] = fd_p[0];
	close(fd_p[1]);
	pipe(fd_p);
	pid = fork();
	if (pid == 0)
	{
		dup2(backup_pipe[0], 0);
		close(fd_p[0]);
		// fd_p[1] = backup_pipe[1];	
		system("cat");
		exit(0);
	}
	wait(&status);
	close(fd_p[1]);
	// close(fd_p[0]);
	// close(fd_p[1]);
	// close(backup_pipe[0]);
	// close(backup_pipe[1]);
	// dup2(backup[0], 0);
	// dup2(backup[1], 1);
}

int main()
{
	test();
}
