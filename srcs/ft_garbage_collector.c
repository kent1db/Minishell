
#include "minishell.h"

void	*malloc_gc(t_list **gc, size_t size)
{
	void	*malloc_ptr;

	malloc_ptr = malloc(size);
	if (!malloc_ptr)
		ft_error_msg("Malloc error", *gc);
	ft_lstadd_front(gc, ft_lstnew(malloc_ptr));
	return (malloc_ptr);
}

char	*ft_strdup_gc(t_list **gc, char *src)
{
	char	*dest;

	dest = ft_strdup(src);
	if (!dest)
		ft_error_msg("Malloc error", *gc);
	ft_lstadd_front(gc, ft_lstnew(dest));
	return (dest);
}
