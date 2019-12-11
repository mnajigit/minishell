/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:17 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 18:00:19 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int  parse_group(t_minishell *mn)
// {

// }

int     parsing(char *line, t_minishell *mn)
{
    if (!(mn->line_cut = split_minishell(line, ';')))
        return (0);
    // if (!(parse_group(mn)))
    //     return (free_line_cut(mn->line_cut));
    return (1);
}