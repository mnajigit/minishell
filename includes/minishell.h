/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:31:28 by mnaji             #+#    #+#             */
/*   Updated: 2019/12/13 17:52:05 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>

typedef struct      s_var
{
    char            	*key;
    char            	*value;
    struct s_var    	*next;
}                   t_var;

typedef enum	e_redir_file
{
	TERM,
	NEXT,
}				t_redir_file;

/*
s_prog :
if nb_prog = 1 +> stdout terminal
else => stdout = prc[NEXT]
*/

typedef struct 	s_prog
{
	char				**cmd;
	char				**file_in;  // <
	char				**file_out;	// >
	char				**file_end; // >>
	unsigned int		nb_file_in;
	unsigned int		nb_file_out;
	unsigned int		nb_file_end;
}				t_prog;

typedef struct	s_processus
{
	char				*prc;
	char				**prc_cut;
	t_prog				*prog;
	unsigned int		nb_prog;
	
}				t_processus;

// typedef struct	s_group
// {
// 	char				*grp;
// 	int					value; // && = 0 ; || == 1
// 	t_processus			*prc;
// 	unsigned int		prc_len;
// 	struct s_group		*next;
// 	t_bool				ret;
// }				t_group;

typedef enum	e_group_type
{
	GRP_AND,
	GRP_OR,
	GRP_PAR,
	GRP_PROC,
}				t_group_type;

typedef struct 	s_group
{
	char				*grp; // pour aider au parsing
	char				*grp_left; //pour aider au parsing
	char				*grp_right; //pour aider au parsing
	t_group_type		type; // && = 0 ; || = 1 ; () == 2 ; proc = 3
	struct s_group		*left;
	struct s_group		*right;
	t_processus			*proc;
}				t_group;

typedef struct  s_minishell
{
	char				**line_cut;
	unsigned int		i_l;
	t_group				*grp;
	unsigned int		grp_len;
    unsigned int		*stdi;
	unsigned int		stdi_len;
	unsigned int		*stdo;
	unsigned int		stdio_len;
}               t_minishell;

typedef struct  s_line
{
    char				**line;
    int					i;
    t_bool				full;
}				t_line;

int				parse_minishell(t_minishell *mn);
char			**split_minishell(char const *s, char c);
int				parse_processus(t_processus *prc);

int     		return_error(char *error, int ret);

int				free_line_cut(char **line_cut, int ret);
int 			free_all(t_line *l, t_minishell *mn);
int 			return_free_line(char **line, int i, int full, char *error);
void    		free_minishell(t_minishell *mn);
int				free_processus(t_processus *prc, int step, int ret);
int				free_programme(t_prog *prog, int ret);

#endif