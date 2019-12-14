/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchudant <cchudant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 07:34:24 by cchudant          #+#    #+#             */
/*   Updated: 2019/12/14 15:34:45 by cchudant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t CHILD = 0;

static void sigterm_handler(int c)
{
	(void)c;
	if (CHILD)
	{
		kill(CHILD, SIGINT);
		CHILD = 0;
	}
	//todo effacer commande que le user est en train d'ecrire
}

void init_signals()
{
	signal(SIGINT, &sigterm_handler);
}

void exec_cmd(t_minishell *mn, t_prog *cmd)
{
	static char *const	c = NULL;
	int					status;
	(void)mn;
	
	if (!(CHILD = fork()))
	{
		printf("I'm a child!\n");
		// child process
		execve(cmd->cmd[0], cmd->cmd, &c);
		exit(1);
	}
	printf("I'm a parent!\n");
	status = 0;
	while (status && !WIFEXITED(status))
		waitpid(CHILD, &status, 0);
	CHILD = 0;
	printf("Child exited with status: %d\n", WEXITSTATUS(status));
}
