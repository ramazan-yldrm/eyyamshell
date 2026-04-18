#include "minishell.h"

t_env	*env_new_node(char *key, char *value)
{
	t_env	*new;

	new = NULL;
	new = gc_malloc(sizeof(t_env), GC_PERM);
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}