#include "minishell.h"

void	env_add_back(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!env_list || !new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
