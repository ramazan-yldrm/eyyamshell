#include "minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env_list)
{
	t_env	*tmp;
	char	*temp_str;
	char	**env_arr;
	int		i;

	i = env_list_size(env_list);
	env_arr = gc_malloc(sizeof(char *) * (i + 1), GC_TEMP);
	if (!env_arr)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			temp_str = gc_strjoin(tmp->key, "=", GC_TEMP);
			env_arr[i] = gc_strjoin(temp_str, tmp->value, GC_TEMP);
			i++;
		}
		tmp = tmp->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
