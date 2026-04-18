#include "minishell.h"

void	env_remove_node(t_env **env_list, char *key)
{
	t_env	*curr;

	if (!env_list || !*env_list)
		return ;
	curr = (*env_list);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			if (curr == *env_list)
				*env_list = curr->next;
			return ;
		}
		curr = curr->next;
	}
}