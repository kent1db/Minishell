
#include "minishell.h"

t_env	*pick_key_and_content(char *envp, t_list **gc, status status)
{
	char	*key;
	char	*content;
	int		i;

	i = ft_strchr_index(envp, '=');
	if (i == -1)
		return (NULL);
	key = ft_substr(envp, 0, i);
	ft_lstadd_front(gc, ft_lstnew(key));
	content = ft_strdup(&envp[i + 1]);
	ft_lstadd_front(gc, ft_lstnew(content));
	if (!key || !content)
		ft_error_msg("Malloc error", *gc);
	return (ft_lstnew_env(key, content, status));
}

t_env	*parse_env(char **envp, t_list **gc)
{
	t_env	*env;
	t_env	*new_elem;

	env = NULL;
	while (*envp)
	{
		new_elem = pick_key_and_content(*envp, gc, status_env);
		if (!new_elem)
			ft_error_msg("Malloc error", *gc);
		ft_lstadd_back_env(&env, new_elem);
		ft_lstadd_front(gc, ft_lstnew(new_elem));
		envp++;
	}
	return (env);
}
