/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:17 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 17:03:59 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     parsing(char *line, t_minishell *mn)
{
    if (!(mn->line_cut = ft_split_line_cut(line, ';')))
        return(0);
    return (1);
}