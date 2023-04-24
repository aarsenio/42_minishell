/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:30 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:00:31 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*word_dup(char const *s, int start, int finish)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (finish - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	count_words(char const *s, char c)
{
	int		count_words;
	int		find;

	count_words = 0;
	find = 0;
	while (*s)
	{
		if (*s == c)
			find = 0;
		else if (*s != c && find == 0)
		{
			count_words++;
			find = 1;
		}
		s++;
	}
	return (count_words);
}

static char	**splitter(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		start_word;

	i = 0;
	j = 0;
	start_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_word >= 0)
		{
			split[j] = word_dup(s, start_word, i);
			start_word = -1;
			j++;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (splitter(split, s, c));
}
