/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:34:16 by adastugu          #+#    #+#             */
/*   Updated: 2026/01/12 18:34:36 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_words(char **words, int i)
{
	while (i >= 0)
	{
		free(words[i--]);
	}
	free(words);
}

int	ft_strlen_char(const char *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i] && !(s[i] == c))
	{
		count++;
		i++;
	}
	return (count);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;
	int	inside;

	i = 0;
	count = 0;
	inside = 0;
	while (s[i])
	{
		if (s[i] != c && !inside)
		{
			count++;
			inside = 1;
		}
		else if (s[i] == c)
			inside = 0;
		i++;
	}
	return (count);
}

static char	*word_dup(const char *s, int *i, char c)
{
	int		j;
	int		word_len;
	char	*word;

	word_len = ft_strlen_char(s, *i, c);
	word = malloc(word_len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < word_len)
		word[j++] = s[(*i)++];
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (j < words)
	{
		while ((s[i] == c))
			i++;
		res[j++] = word_dup(s, &i, c);
		if (!res[j - 1])
			free_words(res, j - 1);
		if (!res[j - 1])
			return (NULL);
	}
	res[j] = NULL;
	return (res);
}
