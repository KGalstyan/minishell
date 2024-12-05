/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:16:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/05 16:59:14 by kgalstya         ###   ########.fr       */
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
	}
	else
	{
		waitpid(pid, NULL, 0);
		kill(pid, 0);
	}
}

int have_dollar(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return(1);
		i++;
	}
	return(0);
}

void change_word(t_data *data, t_data *here, int lim_status, int fd)
{
	char *word;
	char *new_content;
	int i;
	int j;

	i = 0;
	j = 0;
	if(have_dollar(here->input) && lim_status == 0)
	{
		while(here->input[i])
		{
			if(here->input[i] == '$')
			{
				i++;
				j = i;
				while(here->input[i] && (ft_isdigit(here->input[i]) || ft_isalpha(here->input[i]) || here->input[i] == '_'))
					i++;
				word = ft_strndup(here->input, i, j);
				new_content = ft_strdup(get_value_from_env(data->env, word));
				free(word);
				write(fd, new_content, ft_strlen(new_content));
				free(new_content);
			}
			else
				write(fd, &(here->input[i]), 1);
			i++;
		}
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, here->input, ft_strlen(here->input));
		write(fd, "\n", 1);
	}
}

int	heredoc_loop(t_data *data, int fd, char *limiter, int lim_status)
{
	t_data here;

	while (1)
	{
		init_signals(2);
		here.input = readline("> ");
		if (!here.input || ft_strcmp(here.input, limiter) == 0)
		{
			free(here.input);
			here.input = NULL;
			break ;
		}
		if (get_g_exit_status() == 247)
		{
			set_g_exit_status(1);
			return (-1);
		}
		// if(have_dolar(here.input) && lim_status == 0)
		change_word(data, &here, lim_status, fd);
		// write(fd, here.input, ft_strlen(here.input));
		// write(fd, "\n", 1);
		free(here.input);
		here.input = NULL;
	}
	return (close(fd), 0);
}

int	open_heredoc(t_data *data, char *limiter, int lim_status)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		minishell_error2(HEREDOC_FILE, "", strerror(errno));
		set_g_exit_status(EXIT_FAILURE);
		return (-1);
	}
	if (heredoc_loop(data, fd, limiter, lim_status) == -1)
		return (-1);
	close(fd);
	fd = open(HEREDOC_FILE, O_RDONLY);
	if (fd < 0)
	{
		minishell_error2(HEREDOC_FILE, "", strerror(errno));
		set_g_exit_status(EXIT_FAILURE);
		return (-1);
	}
	return (fd);
}
