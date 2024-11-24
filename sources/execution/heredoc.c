/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:16:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/24 13:01:03 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_heredoc_file(struct t_env_export *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		minishell_error2(FORK_ERR, "", "");
	if (pid == 0)
	{
		execve("/bin/rm", (char *[4]){"rm", "-rf", HEREDOC_FILE, NULL},
			list_to_array(env));
        //set_g
	}
	else
	{
		waitpid(pid, NULL, 0);
		kill(pid, 0);
	}
}
// void handle_heredoc_sig(int sig)
// {
//     (void)sig;
//     set_g_exit_status(EXIT_FAILURE);
//     rl_redisplay();
// }

int heredoc_loop(int fd, char *limiter)
{
    char *cur;

    while(1)
    {
		init_signals(2);
        cur = readline("> ");
        if(!cur || ft_strcmp(cur, limiter) == 0)
        {
            free(cur);
            cur = NULL;
            break ;
			// close(fd);
			// return(-1);
        }
        if(get_g_exit_status() == 247)
        {
            set_g_exit_status(1);
            // close(fd);
            return(-1);
        }
        write(fd, cur, ft_strlen(cur));
        write(fd, "\n", 1);
        free(cur);
        cur = NULL;
    }
    close(fd);
	return (0);
}

int open_heredoc(char *limiter)
{
    int fd;
    
    fd = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
    if(fd < 0)
    {
        minishell_error2(HEREDOC_FILE, "", strerror(errno));
        set_g_exit_status(EXIT_FAILURE);
        return (-1);
    }
    if (heredoc_loop(fd, limiter) == -1)
		return (-1);
    close(fd);
    fd = open(HEREDOC_FILE, O_RDONLY);
    if(fd < 0)
    {
        minishell_error2(HEREDOC_FILE, "", strerror(errno));
        set_g_exit_status(EXIT_FAILURE);
        return (-1);
    }
    return (fd);
}
