/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:13:34 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 16:22:59 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_line_cut(char **line_cut)
{
	int		i;

	i = 0;
	while (line_cut[i])
	{
		ft_strdel(&line_cut[i]);
		i++;
	}
	free(line_cut);
	line_cut = NULL;
}

int 	return_free_line(char **line, int i, int full, char *error)
{
	int		end;

	end = i;
	while (i >= 0)
		ft_strdel(&line[i--]);
	if (full == 1)
	{
		i = 99;
		while (i > end)
			ft_strdel(&line[i--]);
	}
	free(line);
	line = NULL;
	if (error)
		ft_putstr(error);
	return (0);
}

void    free_minishell(t_minishell *mn)
{
    free_line_cut(mn->line_cut);
}

int 	free_all(t_line *l, t_minishell *mn)
{
	return_free_line(l->line, l->i, l->full, NULL);
	free_minishell(mn);
    return (0);
}
