/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:27:46 by nranna            #+#    #+#             */
/*   Updated: 2024/12/01 23:13:24 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>

static int	count_words(const char *s, char c);
static char	*create_word(const char *s, int start, int end);
static void	create_result(char **result, const char *s, char c);

char **ft_split(char const *s, char c)
{
	char **result;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	create_result(result, s, c);
	return (result);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	flag;
	int	words;

	i = 0;
	words = 0;
	flag = 1;
	while (s[i])
	{
		if (s[i] == c && flag == 0)
			flag = 1;
		else if ((s[i] != c) && flag == 1)
		{
			words++;
			flag = 0;
		}
		if (s[i] == '\'' || s[i] == '"')
			skip_quotes((char *)s, &i);
		else
			i++;
	}
	return (words);
}

static void	create_result(char **result, const char *s, char c)
{
	int		i;
	int		start;
	int		word_index;

	i = 0;
	word_index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			{
				if (s[i] == '\'' || s[i] == '"')
					skip_quotes((char *)s, &i);
				else
					i++;
			}
			result[word_index] = create_word(s, start, i - 1);
			word_index++;
		}
		else
			i++;
	}
	result[word_index] = NULL;
}

static char	*create_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc((end - start + 2) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

int	free_split(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return (EXIT_FAILURE);
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (EXIT_SUCCESS);
}
