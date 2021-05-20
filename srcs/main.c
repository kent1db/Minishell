
#include "minishell.h"

void	read_command_line(t_env **env, t_list **gc)
{
	char	*line;

	(void)env;
	line = NULL;
	ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		// ft_parse_command_line(gc, line);
		ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

t_all	*init_all(char **envp)
{
	t_all *a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->error = 0;
	a->env = parse_env(envp, &a->gc);
	return (a);
}

int	main(int ac, char **av, char **envp)
{
	t_all *a;

	errno = 0;
	a = init_all(envp);
	// print_banner();
    // read_command_line(&env, &gc);
	ft_lauch_cmd("./ls", a, av[0]);
	ft_printf(1, "%d\n", a->error);
	ft_lstclear(&a->gc, free);
	return (0);
}
