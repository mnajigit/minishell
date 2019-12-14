/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_groups.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 05:20:38 by cchudant          #+#    #+#             */
/*   Updated: 2019/12/14 07:11:25 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int parse_one_group(t_group **dst, char *str, int len);

static void grp_trim(char **str, int *len)
{
	while (*len && **str == ' ')
	{
		(*str)++;
		(*len)--;
	}
	while (*len && (*str)[*len - 1] == ' ')
		(*len)--;
}

static char *ft_strndup(char *str, int len)
{
	int		i;
	char	*res;

	i = 0;
	while (i < len && str[i])
		i++;
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int grp_proc(t_group **dst, char *str, int len)
{
	printf("-> is proc! '%.*s'\n", len, str);
	if (len < 1 || !(*dst = malloc(sizeof(t_group))))
		return (0);
	**dst = (t_group) { .type = GRP_PROC };
	if (!((*dst)->proc = malloc(sizeof(t_processus))))
		return (0);
	*(*dst)->proc = (t_processus) { .prc = ft_strndup(str, len) };
	if (!(*dst)->proc->prc)
		return (0);
	printf("adasd %s\n", (*dst)->proc->prc);
	return (parse_processus((*dst)->proc));
}

static int grp_and(t_group **dst, char *str, int delim, int len)
{
	printf("-> is and! '%.*s', '%.*s'\n", delim, str, len - delim - 2, str + delim + 2);
	if (len < 4 || !(*dst = malloc(sizeof(t_group))))
		return (0);
	**dst = (t_group) { .type = GRP_AND };
	if (!parse_one_group(&(*dst)->left, str, delim))
		return (0);
	if (!parse_one_group(&(*dst)->right, str + delim + 2, len - delim - 2))
		return (0);
	return (1);
}

static int grp_or(t_group **dst, char *str, int delim, int len)
{
	printf("-> is or! '%.*s', '%.*s'\n", delim, str, len - delim - 2, str + delim + 2);
	if (len < 4 || !(*dst = malloc(sizeof(t_group))))
		return (0);
	**dst = (t_group) { .type = GRP_OR };
	if (!parse_one_group(&(*dst)->left, str, delim))
		return (0);
	if (!parse_one_group(&(*dst)->right, str + delim + 2, len - delim - 2))
		return (0);
	return (1);
}

static int grp_par(t_group **dst, char *str, int len)
{
	printf("-> is par! '%.*s'\n", len, str);
	if (len < 2 || !(*dst = malloc(sizeof(t_group))))
		return (0);
	**dst = (t_group) { .type = GRP_PAR };
	if (!parse_one_group(&(*dst)->left, str + 1, len - 2))
		return (0);
	return (1);
}

static int parse_one_group(t_group **dst, char *str, int len)
{
	int		i;
	int		par_count;
	int		squote;
	int		dquote;
	int		escaped;

	grp_trim(&str, &len);
	printf("Parse one group ! '%.*s' (len=%d)\n", len, str, len);
	i = 0;
	par_count = 0;
	squote = 0;
	dquote = 0;
	escaped = 0;
	while (i < len)
	{
		escaped = str[i] == '\\' ? !escaped : 0;
		if (str[i] == '\'')
			squote = !squote;
		else if (!escaped && str[i] == '"')
			dquote = !dquote;
		else if (!squote && str[i] == '(')
			par_count++;
		else if (!squote && str[i] == ')')
			par_count--;
		else if (!squote && !dquote && !par_count && str[i] == '&')
			return (str[i + 1] == '&' ? grp_and(dst, str, i, len) : 0);
		else if (!squote && !dquote && !par_count && str[i] == '|')
			return (str[i + 1] == '|' ? grp_or(dst, str, i, len) : 0);
		if (par_count < 0)
			return (0);
		i++;
	}
	if (str[0] == '(' && str[len - 1] == ')')
		return (grp_par(dst, str, len));
	return (grp_proc(dst, str, len));
}

int			parse_groups(char *str, t_minishell *mn)
{
    return (parse_one_group(&mn->grp, str, ft_strlen(str)));
}