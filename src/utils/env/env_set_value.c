#include "minishell.h"

void	env_set_value(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	env_add_back(env_list, env_new_node(key, value));
}
