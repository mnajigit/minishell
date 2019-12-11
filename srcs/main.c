/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:41:16 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 16:22:49 by mnaji            ###   ########.fr       */
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
	int		i;

	i = 0;
	printf("/n////////////////////////// line_cut ///////////////////////////\n");
	while (mn.line_cut[i])
	{
		printf("[%d] : %s\n", i, mn.line_cut[i]);
		i++;
	}
}

int		main(void)
{
	t_minishell	mn;
	t_line		l;

	ft_bzero(&l, sizeof(t_line));
	l.line = (char**)malloc(sizeof(char*) * 100);
	while (1)
	{
		if (l.line[l.i])
			ft_strdel(&l.line[l.i]);
		ft_putstr("?>");
		if (get_next_line(0, &l.line[l.i]) == -1)
			return (return_free_line(l.line, l.i - 1, l.full, "get_next_line failed !\n"));
		if (!(parsing(l.line[l.i], &mn)))
			return (return_free_line(l.line, l.i - 1, l.full, "parsing failed !\n"));
		if (ft_strcmp(l.line[l.i], "exit") == 0)
			return (free_all(&l, &mn));
		else if (ft_strcmp(l.line[l.i], "printline -a") == 0)           /////////////////////////////////////
			print_all_line(l.line, l.i, l.full);                        /////////////////////////////////////
		print_minishell(mn);											/////////////////////////////////////
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
