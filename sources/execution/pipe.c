/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:41:30 by vkostand          #+#    #+#             */
/*   Updated: 2024/11/22 20:55:35 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_pipes(t_data *data)
{
    int (*fd)[2];
    int i;

    i = 0;
    if(data->pipe_count < 1)
        return (EXIT_SUCCESS);
    fd = malloc(sizeof(int [2]) * data->pipe_count);
    if(!fd)
        return(MALLOC_ERR);
    while(i < data->pipe_count)
    {
        if(pipe(fd[i]) == -1)
        {
            while (i > 0)
			{
				close(fd[i][0]);
				close(fd[i][1]);
                i--;
			}
            free(fd);
            minishell_error("pipe error", "", "");
            return (-1);
        }
        i++;
    }
    data->fd = fd;
    return (EXIT_SUCCESS);
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
    if(data->fd)
    {
        // free(data->fd);
        // data->fd = NULL;
    }
}
