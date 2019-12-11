/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:17 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 18:41:03 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  parse_group(t_minishell *mn)
{
    (void)mn;
    return (1);
}

int     parsing(t_minishell *mn)
{
    if (!(parse_group(mn)))
        return (0);
    return (1);
}