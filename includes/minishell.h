/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:31:28 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/11 18:40:50 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>

typedef struct      s_var
{
    char            *key;
    char            *value;
    struct s_var    *next;
}                   t_var;

typedef struct	s_file
{
	char			*path;
	unsigned int	*stdi;
	unsigned int	stdi_len;
	unsigned int	*stdo;
	unsigned int	stdo_len;
}				t_file;

typedef struct	s_processus
{
	unsigned int	id;
	char			**cmd;
	unsigned int	*stdi;
	unsigned int	stdi_len;
	unsigned int	*stdo;
	unsigned int	stdo_len;
	t_file			*file;
	unsigned int	file_len;

}				t_processus;

typedef struct	s_group
{
	int				value; // && = 0 ; || == 1
	t_processus		*prc;
	unsigned int	prc_len;
	t_bool			ret;
}				t_group;


typedef struct  s_minishell
{
	char			**line_cut;
	unsigned int	i_l;
	t_group			*grp;
	unsigned int	grp_len;
    unsigned int	*stdi;
	unsigned int	stdi_len;
	unsigned int	*stdo;
	unsigned int	stdio_len;
}               t_minishell;

typedef struct  s_line
{
    char			**line;
    int				i;
    t_bool			full;
}				t_line;

int				parsing(t_minishell *mn);

char			**split_minishell(char const *s, char c);

int				free_line_cut(char **line_cut);
int 			free_all(t_line *l, t_minishell *mn);
int 			return_free_line(char **line, int i, int full, char *error);
void    		free_minishell(t_minishell *mn);

#endif