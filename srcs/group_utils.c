/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:39:36 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/12 13:41:28 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_group	*add_new_group(t_group *grp, char *pos)
{
	t_group	*grp_next;

	grp_next = (t_group*)ft_memalloc(sizeof(t_group));
	if (ft_strcmp("left", pos) == 0)
		grp->left = grp_next;
	else if (ft_strcmp("right", pos) == 0)
		grp->right = grp_next;
	return (grp_next);
}