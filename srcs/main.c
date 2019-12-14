/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:41:16 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/14 15:35:04 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_all_line(char **line, int i, t_bool full) ///////////////////////////////////////////////
{
	int		end;

	end = i;
	i--;
	while (i >= 0 && i != end)
	{
		ft_putnbr(i);
		ft_putstr(") ");
		ft_putendl(line[i--]);
		if (i == 0 && full == 1)
		{
			i = 99;
			full = 0;
		}
	}
}

static void print_minishell_proc(t_minishell *mn, t_processus *prc, int prefix)
{
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("-------prc-------\n");
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("%s\n", prc->prc);
	int k = -1;
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("nb_prog = %d\n\n", prc->nb_prog);
	while (++k < (int)prc->nb_prog)
	{
		for (int i = 0; i < prefix; i++) printf(">   ");
		printf("---prog[%d]---\n", k);
		int l = -1;
		while (prc->prog[k].cmd[++l])
		{
			for (int i = 0; i < prefix; i++) printf(">   ");
			printf("arg[%d] = %s\n", l, prc->prog[k].cmd[l]);
		}
		for (int i = 0; i < prefix; i++) printf(">   ");
		printf("nb file in = %d\n", prc->prog[k].nb_file_in);
		l = -1;
		if (prc->prog[k].nb_file_in > 0)
			while (prc->prog[k].file_in[++l])
			{
				for (int i = 0; i < prefix; i++) printf(">   ");
				printf("file_in[%d] = %s\n", l, prc->prog[k].file_in[l]);
			}
		l = -1;
		for (int i = 0; i < prefix; i++) printf(">   ");
		printf("nb file out = %d\n", prc->prog[k].nb_file_out);
		if (prc->prog[k].nb_file_out > 0)
			while (prc->prog[k].file_out[++l])
			{
				for (int i = 0; i < prefix; i++) printf(">   ");
				printf("file_out[%d] = %s\n", l, prc->prog[k].file_out[l]);
			}
		l = -1;
		for (int i = 0; i < prefix; i++) printf(">   ");
		printf("nb file end = %d\n", prc->prog[k].nb_file_end);
		if (prc->prog[k].nb_file_end > 0)
			while (prc->prog[k].file_end[++l])
			{
				for (int i = 0; i < prefix; i++) printf(">   ");
				printf("file_end[%d] = %s\n", l, prc->prog[k].file_end[l]);
			}
		//exec_cmd(mn, &prc->prog[k]);
	}
}

static void print_minishell_grp(t_minishell *mn, t_group *grp, int prefix)
{
	static char *grps[] = { "AND", "OR", "PAR", "PROC" };
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("!!!! GROUP TYPE : %s\n", grps[grp->type]);
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("!!-> left : %p\n", grp->left);
	if (grp->left) print_minishell_grp(mn, grp->left, prefix + 1);
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("!!-> right : %p\n", grp->right);
	if (grp->right) print_minishell_grp(mn, grp->right, prefix + 1);
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("!!-> proc : %p\n", grp->proc);
	if (grp->proc) print_minishell_proc(mn, grp->proc, prefix);
	for (int i = 0; i < prefix; i++) printf(">   ");
	printf("!!!! END GROUP TYPE : %s\n\n", grps[grp->type]);
}

static void	print_minishell(t_minishell *mn)				/////////////////////////////////////////////////
{
	printf("/n////////////////////////// line_cut ///////////////////////////\n");
	printf("[%d] : %s\n", mn->i_l, mn->line_cut[mn->i_l]);

	print_minishell_grp(mn, mn->grp, 0);
}

static int	check_quote(char *line)
{
	int		dbquote;
	int		spquote;
	int		i;

	dbquote = -1;
	spquote = -1;
	i = -1;
	while (line[++i])
	{
		if (((i == 0 && line[i] == '"') || (line[i] == '"' && line[i - 1] != '\\')) && spquote == -1)
			dbquote *= -1;
		else if (line[i] == '\'' && dbquote == -1)
			spquote *= -1;
	}
	if (dbquote == -1 && spquote == -1)
		return (1);
	return (0);
}

static int	line_join_quote(t_line *l)
{
	char	*buff_join;

	ft_putstr("quote>");
	if (get_next_line(0, &buff_join) == -1)
		return (0);
	l->line[l->i] = ft_strjoin_free(l->line[l->i], l->line[l->i], buff_join);
	free(buff_join);
	return (1);
}

int		main(void)
{
	t_minishell	mn;
	t_line		l;
	int			ret;

	init_signals();
	mn = (t_minishell) { 0 };
	l = (t_line) { 0 };
	l.line = (char**)ft_memalloc(sizeof(char*) * 100);
	while (1)
	{
		if (l.line[l.i])
			ft_strdel(&l.line[l.i]);
		ft_putstr("?>");
		if (get_next_line(0, &l.line[l.i]) == -1)
			return (return_free_line(l.line, l.i - 1, l.full, "get_next_line failed !\n"));
		while (!check_quote(l.line[l.i]))
			if (!line_join_quote(&l))
				return (return_free_line(l.line, l.i, l.full, "join quote failed !\n"));
		if (!(mn.line_cut = split_minishell(l.line[l.i], ';')))
        	return (return_free_line(l.line, l.i, l.full, "error parsing !\n"));
		mn.i_l = 0;
		while (mn.line_cut[mn.i_l])
		{
			if (!(ret = parse_minishell(&mn)))
			 	return (return_free_line(l.line, l.i, l.full, "parsing failed !\n"));
			if (ret == -1)
				break ;
			print_minishell(&mn);													/////////////////////////////////////
			if (ft_strcmp(mn.line_cut[mn.i_l], "exit") == 0)
				return (free_all(&l, &mn));
			else if (ft_strcmp(mn.line_cut[mn.i_l], "printline -a") == 0)           /////////////////////////////////////
				print_all_line(l.line, l.i, l.full); 								/////////////////////////////////////
			// free_minishell(&mn);
			mn.i_l++;
		}
		free_line_cut(mn.line_cut, 0);
		if (l.i == 99)
		{
			l.i = -1;
			l.full = 1;
		}
		l.i++;
	}
	return (0);
}
