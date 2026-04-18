#include "minishell.h"

void	gc_free_all(void)
{
	t_gc	**collector;
	t_gc	*curr;
	t_gc	*tmp;

	collector = get_collector();
	if (!collector || !*collector)
		return ;
	curr = *collector;
	while (curr)
	{
		tmp = curr->next;
		if (curr->value)
		{
			free(curr->value);
			curr->value = NULL;
		}
		free(curr);
		curr = tmp;
	}
	*collector = NULL;
}
