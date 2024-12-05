/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgalstya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:16:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/05 20:45:01 by kgalstya         ###   ########.fr       */
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
	if(!here->input)
		return ;
	if(have_dollar(here->input) && lim_status == 0)
	{
		while(here->input[i])
		{
			if(here->input[i] == '$')
			{
				i++;
				j = i;
				if(here->input[i] == '$')
				{
					write(fd, "\n", 1);
					return ;
				}
				while(here->input[i] && (ft_isdigit(here->input[i]) || ft_isalpha(here->input[i]) || here->input[i] == '_'))
					i++;
				word = ft_strndup(here->input, i, j);
				new_content = ft_strdup(get_value_from_env(data->env, word));
				if(new_content)
				{
					free(word);
					write(fd, new_content, ft_strlen(new_content) + 1);
					if(here->input[i])
						write(fd, &(here->input[i]), 1);
					free(new_content);
				}
			}
			else
			{
				write(fd, &(here->input[i]), 1);
				i++;
			}
		}
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, here->input, ft_strlen(here->input) + 1);
		write(fd, "\n", 1);
	}
}

char	*get_key_from_env(t_data *data)
{
	struct t_env_export	*temp;

	temp = data->env;
	if (data->value && !ft_strcmp(data->value, ft_itoa(get_g_exit_status())))
		return ("$?");
	while (temp)
	{
		if (temp->value && (ft_strcmp(temp->value, data->value) == 0))
			return (ft_strjoin("$", temp->key));
		temp = temp->next;
	}
	return (data->value);
}

int	heredoc_loop(t_data *data, int fd, char *limiter, int lim_status)
{
	t_data here;

	data->value = ft_strdup(limiter);
	printf("%s\n", data->value);
	data->new_limiter = ft_strdup(get_key_from_env(data));
	printf("%s\n", data->new_limiter);
	free(data->value);
	while (1)
	{
		init_signals(2);
		here.input = readline("> ");
		if (!here.input || ft_strcmp(here.input, data->new_limiter) == 0)
		{
			free(here.input);
			here.input = NULL;
			break ;
		}
		if (get_g_exit_status() == 247)
		{
			set_g_exit_status(1);
			free(here.input);
			free(data->new_limiter);
			return (-1);
		}
		change_word(data, &here, lim_status, fd);
		here.input = NULL;
	}
	free(data->new_limiter);
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
