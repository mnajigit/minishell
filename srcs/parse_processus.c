/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_processus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:43:37 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/13 18:51:20 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int 	malloc_file(t_prog *prog)
{
	if (prog->nb_file_in > 0)
		if (!(prog->file_in = (char**)ft_memalloc(sizeof(char*) * (prog->nb_file_in + 1))))
			return (0);
	if (prog->nb_file_out > 0)
		if (!(prog->file_out = (char**)ft_memalloc(sizeof(char*) * (prog->nb_file_out + 1))))
		{
			free(prog->file_in);
			return (0);
		}
	if (prog->nb_file_end > 0)
		if (!(prog->file_end = (char**)ft_memalloc(sizeof(char*) * (prog->nb_file_end + 1))))
		{
			free(prog->file_in);
			free(prog->file_out);
			return (0);
		}
	return (1);
}

static int	malloc_prog_file(t_prog *prog, char *line)
{
	int		i;
	int		dbquote;
	int		spquote;

	i = -1;
	dbquote = -1;
	spquote = -1;
	while (line[++i])
	{
		if (((i == 0 && line[i] == '"') || (line[i] == '"' && line[i - 1] != '\\')) && spquote == -1)
			dbquote *= -1;
		else if (line[i] == '\'' && dbquote == -1)
			spquote *= -1;
		else if (line[i] == '>' && line[i + 1] == '>' && dbquote == -1 && spquote == -1)
		{
			prog->nb_file_end++;
			i++;
		}
		else if (line[i] == '>' && dbquote == -1 && spquote == -1)
			prog->nb_file_out++;
		else if (line[i] == '<' && dbquote == -1 && spquote == -1)
			prog->nb_file_in++;
	}
	return (malloc_file(prog));
}

static int	get_value_prog(t_prog *prog, char **arg_tmp)
{
	int		i;
	int		in;
	int		out;
	int		end;
	int		cmd;

	i = -1;
	in = 0;
	out = 0;
	end = 0;
	cmd = 0;
	while (arg_tmp[++i])
	{
		if (arg_tmp[i][0] == '>' && arg_tmp[i][1] == '>')
		{
			if (!(prog->file_end[end++] = ft_strdup(arg_tmp[i + 1])))
				return (0);
		}
		else if (arg_tmp[i][0] == '>')
		{
			if (!(prog->file_out[out++] = ft_strdup(arg_tmp[i + 1])))
				return (0);
		}
		else if (arg_tmp[i][0] == '<')
		{
			if (!(prog->file_in[in++] = ft_strdup(arg_tmp[i + 1])))
				return (0);
		}
		else
		{
			if (!(prog->cmd[cmd++] = ft_strdup(arg_tmp[i])))
				return (0);
		}
	}
	return (1);
}

static int	malloc_prog_cmd(t_prog *prog, char **arg_tmp)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (arg_tmp[++i])
	{
		if (arg_tmp[i][0] != '<' && arg_tmp[i][0] != '>')
			count++;
	}
	if (!(prog->cmd = (char**)ft_memalloc(sizeof(char*) * (count + 1))))
		return (0);
	return (1);
}

static int	parse_programme(t_prog *prog, char *line)
{
	char	**arg_tmp;

	if (!(malloc_prog_file(prog, line)))
		return (0);
	if (!(arg_tmp = split_minishell(line, ' ')))
		return (free_programme(prog, 0));
	if (!(malloc_prog_cmd(prog, arg_tmp)))
	{
		free_line_cut(arg_tmp, 0);
		return (free_programme(prog, 0));
	}
	if (!(get_value_prog(prog, arg_tmp)))
	{
		free_line_cut(arg_tmp, 0);
		return (free_programme(prog, 0));
	}
	free_line_cut(arg_tmp, 0);
	return (1);
}

int		parse_processus(t_processus *prc)
{
	unsigned int	i;

	prc->nb_prog = 0; // prc est sense etre initialise avant
	if (!(prc->prc_cut = split_minishell(prc->prc, '|')))
		return (0);
	while (prc->prc_cut[prc->nb_prog])
		prc->nb_prog++;
	if (!(prc->prog = (t_prog*)ft_memalloc(sizeof(t_prog) * prc->nb_prog)))
		return (free_processus(prc, 0, 0));
	i = -1;
	while (++i < prc->nb_prog)
		if (!(parse_programme(&prc->prog[i], prc->prc_cut[i])))
			return (free_processus(prc, 1, 0));
	return (1);
}