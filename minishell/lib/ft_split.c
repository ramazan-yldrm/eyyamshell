/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:27:23 by asari             #+#    #+#             */
/*   Updated: 2025/06/27 08:24:46 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	initilazier(int *a, int *b, int *c)
{
	*a = -1;
	*b = 0;
	*c = 0;
}

static int	word_counter(const char *s, char c)
{
	int	word_count;
	int	flag;

	word_count = 0;
	flag = 0;
	while (*s != '\0')
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			word_count++;
		}
		else if (*s == c && flag == 1)
			flag = 0;
		s++;
	}
	return (word_count);
}

static char	**fill_array(const char *s, char **array, char c)
{
	int	start;
	int	end;
	int	index;
	int	len;

	initilazier(&start, &end, &index);
	while (s[end] != '\0')
	{
		if (s[end] != c && start < 0)
			start = end;
		if ((s[end] == c || s[end + 1] == '\0') && start >= 0)
		{
			len = end - start;
			if (s[end] != c)
				len++;
			array[index] = ft_substr(s, start, len);
			if (array[index] == NULL)
				return (free_all(array));
			index++;
			start = -1;
		}
		end++;
	}
	array[index] = NULL;
	return (array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = word_counter(s, c);
	array = malloc(sizeof(char *) * (word_count + 1));
	if (array == NULL)
		return (NULL);
	array = fill_array(s, array, c);
	return (array);
}
