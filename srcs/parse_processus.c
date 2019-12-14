/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_processus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:43:37 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/13 21:39:17 by mnaji            ###   ########.fr       */
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
			i++;
		}
		else if (arg_tmp[i][0] == '>')
		{
			if (!(prog->file_out[out++] = ft_strdup(arg_tmp[i + 1])))
				return (0);
			i++;
		}
		else if (arg_tmp[i][0] == '<')
		{
			if (!(prog->file_in[in++] = ft_strdup(arg_tmp[i + 1])))
				return (0);
			i++;
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

static char	*add_space_around(char *line, int i, int nb_char)
{
	char	*left;
	char	*right;
	int		j;

	j = -1;
	if (!(left = ft_memalloc(sizeof(char) * (i + 3 + nb_char))))
		return (NULL);
	while (++j < i)
		left[j] = line[j];
	left[j++] = ' ';
	left[j++] = line[i];
	if (nb_char == 2)
		left[j++] = line[i + 1];
	left[j++] = ' ';
	if (!(right = ft_strdup(&line[i + nb_char])))
	{
		ft_strdel(&left);
		return (NULL);
	}
	if (!(line = ft_strjoin_free(line, left, right)))
	{
		ft_strdel(&left);
		ft_strdel(&right);
		return (NULL);
	}
	ft_strdel(&left);
	ft_strdel(&right);
	return (line);
}

static char	*add_space_prog(char *line)
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
		else if (i != 0 && dbquote == -1 && spquote == -1 && line[i] == '>' && line[i + 1] == '>')
		{
			if (!(line = add_space_around(line, i, 2)))
				return (NULL);
			i += 2;
		}
		else if (i != 0 && dbquote == -1 && spquote == -1 && (line[i] == '<' || line[i] == '>'))
			if (!(line = add_space_around(line, i++, 1)))
				return (NULL);
	}
	return (line);
}

static int	cut_quote_args(t_prog *prog)
{
	int		i;

	i = -1;
	while (prog->cmd[++i])
	{
		if (prog->cmd[i][0] == '"' || prog->cmd[i][0] == '\'')
		{
			if (!(prog->cmd[i] = ft_strdup_free(prog->cmd[i], &prog->cmd[i][1])))
				return (0);
			prog->cmd[i][ft_strlen(prog->cmd[i]) - 1] = '\0';
		}
	}
	return (1);
}

static int	parse_programme(t_prog *prog, char *line)
{
	char	**arg_tmp;

	if (!(line = add_space_prog(line)))
		return (0);
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
	if (!(cut_quote_args(prog)))
		return (0);
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