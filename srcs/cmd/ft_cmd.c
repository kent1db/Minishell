#include "minishell.h"

int	is_cmd_exist(char *cmd)
{
	return (1);
}

char	**list_cmd_done(t_list **gc)
{
	char **cmd_done;

	cmd_done = malloc_gc(gc, sizeof(char *) * 7);
	cmd_done[0] = "echo";
	cmd_done[1] = "cd";
	cmd_done[2] = "pwd";
	cmd_done[3] = "export";
	cmd_done[4] = "unset";
	cmd_done[5] = "env";
	cmd_done[6] = "exit";
	return (cmd_done);
}

void ft_lauch_cmd(void *cmds, t_list **gc)
{
	void	(**ft_instruction)(t_list **, t_list **, int);
	char	**cmd_done;

	cmd_done = list_cmd_done(gc);
	printf("%s\n", cmd_done[1]);
}