/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:57:37 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 13:58:08 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	word_count(const char *s, char c1, char c2)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c1 && s[i] != c2 && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c1 || s[i] == c2)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*fill_words(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_str(char **str, int count)
{
	while (count >= 0)
		free(str[count--]);
	free(str);
	return (NULL);
}

char	**ft_split_double(const char *s, char c1, char c2, int i)
{
	int		end;
	int		start;
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((word_count(s, c1, c2) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	start = 0;
	while (i < word_count(s, c1, c2))
	{
		while ((s[start] == c1 || s[start] == c2) && s[start] != '\0')
			start++;
		end = start;
		while (s[end] != c1 && s[end] != c2 && s[end] != '\0')
			end++;
		str[i] = fill_words(s, start, end);
		if (!str[i])
			return (free_str(str, i - 1));
		start = end;
		i++;
	}
	str[i] = NULL;
	return (str);
}
