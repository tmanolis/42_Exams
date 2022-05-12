#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

# define FAILURE 1

int	ft_putstr2(char *str, char *cmd)
{
	while (*str)
		write(2, str++, 1);
	if (cmd)
	{
		while (*cmd)
			write(2, cmd++, 1);
	}
	write(2, "\n", 1);
	return (1);
}

int	ft_execute(int i, char **argv, char **envp, int tmp_fd)
{
	argv[i] = NULL;
	close(tmp_fd);
	execve(argv[0], argv, envp);
	return (ft_putstr2("error: cannot execute ", argv[0]);
}

int	main(int argc, char **argv, char *envp[])
{
	int i;
	int pid;
	int tmp_fd;
	int tube_fd[2];

	(void)argc;
	i = 0;
	pid = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
				return ("error: cd: bad arguments", NULL);
			if (chdir(argv[1]) != 0)
				return ("error: cd: cannot change directory to ", argv[1]);
		}
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				if (ft_execute(i, argv, envp, tmp_fd))
					return (FAILURE);
			}
			else
			{
				close(tmp_fd);
				waitpid(pid, NULL, 0);
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{
			pipe(tube_fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp_fd, STDIN_FILENO);
				dup2(tube_fd[1], STDOUT_FILENO);
				close(tube_fd[0]);
				close(tube_fd[1]);
				if (ft_execute(i, argv, envp, tmp_fd))
					return (FAILURE);
			}
			else
			{
				close(tube_fd[1]);
				close(tmp_fd);
				tmp_fd = tube_fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}
