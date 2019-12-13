/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:36:29 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/12 20:43:07 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_word(char const *s, char c)
{
	int		i;
	int		count_word;
    int     db_quote;
    int     sp_quote;

	i = 0;
    db_quote = -1;
    sp_quote = -1;
	count_word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && (sp_quote == -1 || db_quote == -1))
		{
			i++;
			if (s[i] == '\0')
				return (count_word);
		}
		while ((s[i] != c || db_quote == 1 || sp_quote == 1) && s[i] != '\0')
		{
			if (((i == 0 && s[i] == '"') || (s[i] == '"' && s[i - 1] != '\\')) && sp_quote == -1)
        		db_quote *= -1;
			else if (s[i] == '\'' && db_quote == -1)
				sp_quote *= -1;
			if (s[i] == '\0')
				return (count_word + 1);
			i++;
		}
		count_word++;
	}
	return (count_word);
}

static int	ft_size_word(char *str, char c)
{
	int		i;
	int		count;
	int     db_quote;
    int     sp_quote;

	i = 0;
	count = 0;
	db_quote = -1;
    sp_quote = -1;
	while ((str[i] != c || db_quote == 1 || sp_quote == 1) && str[i] != '\0')
	{
		if (((i == 0 && str[i] == '"') || (str[i] == '"' && str[i - 1] != '\\')) && sp_quote == -1)
        	db_quote *= -1;
		else if (str[i] == '\'' && db_quote == -1)
			sp_quote *= -1;
		count++;
		i++;
	}
	return (count);
}

static int	ft_cpy_ligne(char *tab, char *s, int i, char c)
{
	int		t;
	int     db_quote;
    int     sp_quote;

	t = 0;
	db_quote = -1;
    sp_quote = -1;
	while ((s[i] != c || db_quote == 1 || sp_quote == 1) && s[i] != 0)
	{
		if (((i == 0 && s[i] == '"') || (s[i] == '"' && s[i - 1] != '\\')) && sp_quote == -1)
        	db_quote *= -1;
		else if (s[i] == '\'' && db_quote == -1)
			sp_quote *= -1;
		tab[t] = s[i];
		i++;
		t++;
	}
	tab[t] = '\0';
	return (i);
}

static char	**ft_return_tab(char *s, char **tab, int ligne, char c)
{
	if (*s - 1 != c)
		tab[ligne] = 0;
	else
		tab[ligne - 1] = 0;
	return (tab);
}

char		**split_minishell(char const *s, char c)
{
	char	**tab;
	int		i;
	int		ligne;

	if (!s || !c || !(tab = (char**)malloc(sizeof(char*) *\
					(ft_count_word(s, c) + 1))))
		return (NULL);
	ligne = 0;
	i = 0;
	while (ligne < ft_count_word(s, c))
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (!(tab[ligne] = (char*)malloc(sizeof(char) * \
						ft_size_word((char*)&s[i], c) + 1)))
		{
			while (ligne-- >= 0)
				free(tab[ligne]);
			free(tab);
			return (NULL);
		}
		i = ft_cpy_ligne(tab[ligne], (char*)s, i, c);
		ligne++;
	}
	return (ft_return_tab((char*)&s[i], tab, ligne, c));
}
