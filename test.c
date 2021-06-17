#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
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
		// backup_pipe[0] = fd_p[0];
		close(fd_p[0]);
		dup2(fd_p[1], 1);
		close(fd_p[1]);
		dprintf(1, "yes\n");
		system("ls");
		exit(0);
	}
	dprintf(1, "yes\n");
	wait(&status);
	printf("le ls est fait\n");
	// pipe(fd_p);
	pid = fork();
	if (pid == 0)
	{
		// fd_p[1] = backup_pipe[1];	
		close(fd_p[1]);
		dup2(fd_p[0], 0);
		close(fd_p[0]);
		fd_p[0] = backup_pipe[0];	
		dprintf(1, "why\n");
		system("cat");
		exit(0);
	}
	dprintf(1, "okay\n");
	wait(&status);
	dprintf(1, "suce\n");
	close(fd_p[0]);
	close(fd_p[1]);
	close(backup_pipe[0]);
	close(backup_pipe[1]);
	dup2(backup[0], 0);
	dup2(backup[1], 1);
	printf("cat est fait");
	return (0);
}