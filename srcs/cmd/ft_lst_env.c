
#include "minishell.h"

t_env	*ft_lstnew_env(char *key, char *content, status status)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->content = content;
	elem->status = status;
	elem->next = NULL;
	return (elem);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*last;

	last = ft_lstlast_env(*alst);
	if (last != NULL)
		last->next = new;
	else
		*alst = new;
}

void	ft_lst_remove_key(t_env **env, char *key)
{
	t_env *begin;

	begin = *env;
	if (!ft_strcmp((*env)->key, key))
	{
		*env = (*env)->next;
		return ;
	}
	while (*env && (*env)->next)
	{
		if (!ft_strcmp((*env)->next->key, key))
		{
			(*env)->next = (*env)->next->next;
			*env = begin;
			return ;
		}
		*env = (*env)->next;
	}
	*env = begin;
}
