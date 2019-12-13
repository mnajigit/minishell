/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:13:34 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/13 17:55:22 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int 	free_line_cut(char **line_cut, int ret)
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
    return (ret);
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

int		free_programme(t_prog *prog, int ret)
{
	int		i;

	i = -1;
	while (prog->file_in[++i] != NULL)
		ft_strdel(&prog->file_in[i]);
	i = -1;
	while (prog->file_out[++i] != NULL)
		ft_strdel(&prog->file_out[i]);
	i = -1;
	while (prog->file_end[++i] != NULL)
		ft_strdel(&prog->file_end[i]);
	i = -1;
	while (prog->cmd[++i])
		ft_strdel(&prog->cmd[i]);
	if (prog->cmd)
		free(prog->cmd);
	if (prog->nb_file_in > 0)
		free(prog->file_in);
	if (prog->nb_file_out > 0)
		free(prog->file_out);
	if (prog->nb_file_end > 0)
		free(prog->file_end);
	return (ret);
}

int		free_processus(t_processus *prc, int step, int ret)
{
	unsigned int	i;

	ft_strdel(&prc->prc);
	i = -1;
	while (prc->prc_cut[++i])
		ft_strdel(&prc->prc_cut[i]);
	free(&prc->prc_cut);
	prc->prc_cut = NULL;
	i = -1;
	if (prc->nb_prog > 0)
		while (++i < prc->nb_prog)
			free(&prc->prog[i]);
	if (step > 0)
	{
		free(prc->prog);
		prc->prog = NULL;
	}
	return (ret);
}

void    free_minishell(t_minishell *mn)
{
    free_line_cut(mn->line_cut, 0);
}

int 	free_all(t_line *l, t_minishell *mn)
{
	return_free_line(l->line, l->i, l->full, NULL);
	free_minishell(mn);
    return (0);
}
