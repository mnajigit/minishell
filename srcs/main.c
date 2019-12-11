/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:41:16 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 18:14:43 by mnaji            ###   ########.fr       */
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

static void	print_minishell(t_minishell mn)				/////////////////////////////////////////////////
{
	printf("/n////////////////////////// line_cut ///////////////////////////\n");
	printf("[%d] : %s\n", mn.i_l, mn.line_cut[mn.i_l]);
}

int		main(void)
{
	t_minishell	mn;
	t_line		l;

	mn = (t_minishell) { 0 };
	ft_bzero(&l, sizeof(t_line));
	l.line = (char**)malloc(sizeof(char*) * 100);
	while (1)
	{
		if (l.line[l.i])
			ft_strdel(&l.line[l.i]);
		ft_putstr("?>");
		if (get_next_line(0, &l.line[l.i]) == -1)
			return (return_free_line(l.line, l.i - 1, l.full, "get_next_line failed !\n"));
		if (!(mn.line_cut = split_minishell(l.line[l.i], ';')))
        	return (return_free_line(l.line, l.i, l.full, "error parsing !\n"));
		mn.i_l = 0;
		while (mn.line_cut[mn.i_l])
		{
			print_minishell(mn);										/////////////////////////////////////
			mn.i_l++;
		}
		// if (!(parsing(l.line[l.i], &mn)))
		// 	return (return_free_line(l.line, l.i - 1, l.full, "parsing failed !\n"));
		if (ft_strcmp(l.line[l.i], "exit") == 0)
			return (free_all(&l, &mn));
		else if (ft_strcmp(l.line[l.i], "printline -a") == 0)           /////////////////////////////////////
			print_all_line(l.line, l.i, l.full);                        /////////////////////////////////////
		if (l.i == 99)
		{
			l.i = -1;
			l.full = 1;
		}
		l.i++;
		free_minishell(&mn);
	}
	return (0);
}
