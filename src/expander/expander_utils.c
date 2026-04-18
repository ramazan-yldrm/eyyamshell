#include "minishell.h"

char	*replace_str(char *str, char *rep, int start_i, int end_i)
{
	char	*result;
	int		length;
	int		i;
	int		j;

	if (!str || !rep || start_i < 0 || end_i < start_i)
		return (NULL);
	length = ft_strlen(str) - (end_i - start_i + 1) + ft_strlen(rep);
	result = gc_malloc(length + 1, GC_TEMP);
	i = -1;
	while (++i < start_i)
		result[i] = str[i];
	j = -1;
	while (rep[++j])
		result[i++] = rep[j];
	j = end_i;
	while (str[++j])
		result[i++] = str[j];
	result[i] = '\0';
	return (result);
}

char	*ft_ternary_str(char *value, char *default_str)
{
	if (value)
		return (value);
	return (default_str);
}
