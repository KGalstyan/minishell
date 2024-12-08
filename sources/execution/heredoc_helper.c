/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:39:36 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 20:52:24 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_heredoc_file(void)
{
	unlink(HEREDOC_FILE);
}

// void	remove_heredoc_file(t_env_export *env)
// {
// pid_t	pid;

// pid = fork();
// if (pid == -1)
// 	minishell_error2(FORK_ERR, "", "");
// if (pid == 0)
// {
// 	execve("/bin/rm", (char *[4]){"rm", "-rf", HEREDOC_FILE, NULL},
// 		list_to_array(env));
// }
// else
// {
// 	waitpid(pid, NULL, 0);
// 	kill(pid, 0);
// }
// }

int	have_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
