/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:16:50 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/07 22:51:43 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_new_content(struct s_env_export *env, char *input, int *i, int fd)
{
	char	*word;
	char	*new_content;
	int		j;

	(*i)++;
	j = *i;
	while (input[*i] && (ft_isdigit(input[*i]) || ft_isalpha(input[*i])
			|| input[*i] == '_'))
		(*i)++;
	word = ft_strndup(input, *i, j);
	if (!word)
		return ;
	new_content = ft_strdup(get_value_from_env(env, word));
	free(word);
	if (!new_content)
		return ;
	write(fd, new_content, ft_strlen(new_content) + 1);
	if (input[*i])
		write(fd, &(input[*i]), 1);
	free(new_content);
	(void)i;
}

void	change_word(t_data *data, t_data *here, int lim_status, int fd)
{
	int	i;

	i = 0;
	if (!here->input)
		return ;
	if (have_dollar(here->input) && lim_status == 0)
	{
		while (here->input[i])
		{
			if (here->input[i] == '$' && here->input[i + 1] == '$')
				break ;
			if (here->input[i] == '$')
				get_new_content(data->env, here->input, &i, fd);
			else
			{
				write(fd, &(here->input[i]), 1);
				i++;
			}
		}
		write(fd, "\n", 1);
	}
	else
		ft_putendl_fd(here->input, fd);
}

char	*get_key_from_env(t_data *data)
{
	t_env_export	*temp;
	char			*tmp;

	temp = data->env;
	tmp = ft_itoa(get_g_exit_status());
	if (data->value && !ft_strcmp(data->value, tmp))
		return (free(tmp), ft_strdup("$?"));
	free(tmp);
	while (temp)
	{
		if (temp->value && (ft_strcmp(temp->value, data->value) == 0))
			return (ft_strjoin("$", temp->key));
		temp = temp->next;
	}
	return (ft_strdup(data->value));
}

int	heredoc_loop(t_data *data, int fd, char *limiter, int lim_status)
{
	t_data	here;

	data->value = ft_strdup(limiter);
	data->new_limiter = get_key_from_env(data);
	free(data->value);
	init_signals(3);
	while (1)
	{
		here.input = readline("> ");
		if (!here.input || ft_strcmp(here.input, data->new_limiter) == 0)
		{
			free(here.input);
			here.input = NULL;
			break ;
		}
		if (get_g_exit_status() == 247)
			return (free(here.input), free(data->new_limiter), -1);
		change_word(data, &here, lim_status, fd);
		if (here.input)
			free(here.input);
		here.input = NULL;
	}
	return (free(data->new_limiter), close(fd), 0);
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
