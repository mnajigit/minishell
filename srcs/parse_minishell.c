/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:17 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/13 18:36:05 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_bracket(char *line)
// {
// 	int		i;
// 	int		brk_open;
// 	int		brk_close;
// 	char	dbquote;
// 	char	spquote;

// 	i = -1;
// 	dbquote = -1;
// 	spquote = -1;
// 	brk_open = 0;
// 	brk_close = 0;
// 	while (line[++i])
// 	{
// 		if (line[i] == '(' && dbquote == -1 && spquote == -1)
// 			brk_open++;
// 		else if (line[i] == ')' && dbquote == -1 && spquote == -1)
// 			brk_close++;
// 		else if (((i == 0 && line[i] == '"') || (line[i -1] != '\\' && line[i] == '"')) && spquote == -1)
// 			dbquote *= -1;
// 		else if (line[i] == '\'' && dbquote == -1)
// 			spquote *= -1;
// 		if (brk_open < brk_close)
// 			return (-1);
// 	}
// 	if (brk_close != brk_open)
// 		return (-1);
// 	return (brk_close);
// }

// static int	parse_group_simple(char *line, t_group *grp)
// {
// 	int		i;
// 	int		nb_grp;

// 	i = -1;
// 	nb_grp = 0;
// 	while (line[++i])
// 	{
// 		if (line[i] == '&' && line[i + 1] == '&')
// 			grp = add_new_group(grp, "left", GRP_AND);
// 	}
// 	return (1);
// }

// static int	parse_group(char *line, t_group *grp)
// {
// 	int		nb_brk;

// 	(void)grp;
// 	if ((nb_brk = check_bracket(line)) == -1)
// 		return (return_error("Please close bracket!\n", -1));
// 	// if (nb_brk == 0)
// 	// 	parse_group_simple(line, grp);
// 	return (1);
// }

int			parse_minishell(t_minishell *mn)
{
	// int		ret; // 0 => exit total ; -1 relaunch command ; 1 pas d'erreur

	// if ((ret = parse_group(mn->line_cut[mn->i_l], mn->grp)) != 1)
	// 	return (!ret ? free_line_cut(mn->line_cut, ret) : ret);
	// PARSE PROCESSUS !!
	mn->grp = (t_group*)ft_memalloc(sizeof(t_group) * 2);
	mn->grp[0].proc = ft_memalloc(sizeof(t_processus) * 2);
	mn->grp[0].proc->prc = ft_strdup(mn->line_cut[mn->i_l]);
	parse_processus(mn->grp[0].proc);
    return (1);
}