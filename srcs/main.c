
#include "minishell.h"

void	read_command_line(t_env **env, t_list **gc)
{
	char	*line;

	(void)env;
	line = NULL;
	ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		// ft_parse_command_line(gc, line);
		ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *env;
	t_list *gc;
	int		i = 0;

	gc = NULL;
	env = parse_env(envp, &gc);
	// print_banner();
    // read_command_line(&env, &gc);
	ft_lauch_cmd(NULL, &gc);
	ft_lstclear(&gc, free);
	return (0);
}
