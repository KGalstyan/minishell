/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:31:25 by vkostand          #+#    #+#             */
/*   Updated: 2024/12/02 16:24:08 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_tokens(t_data *data)
{
	if (data->input[data->i] == '<' || data->input[data->i] == '>')
		return (1);
	else if (data->input[data->i] == '$' || data->input[data->i] == '|')
		return (1);
	else if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		return (1);
	return (0);
}

int	create_tokens(t_data *data)
{
	data->i = 0;
	data->j = 0;
	while (data->input[data->i])
	{
		data->quotes_flag = NONE;
		data->j = data->i;
		if (check_pipe_red_env(data))
			continue ;
		else if (check_quotes(data))
			continue ;
		else if (check_space(data))
			continue ;
		while (data->input[data->i] && data->input[data->i] != ' ')
		{
			if (check_special_tokens(data))
				break ;
			data->i++;
		}
		data->type = WORD;
		if (fill_tokens(data, data->i, data->j,
				data->quotes_flag) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// void print_data(t_data *data)
// {
//     t_token *pr_token = data->tokens;
//     while(pr_token != NULL)
//     {

//         printf(RED "token --> " RESET_COLOR);
//         printf(GREEN "[%s]" RESET_COLOR, pr_token->original_content);
//         printf("  (%d) -->", pr_token->quotes);
//         printf(YELLOW " type(%d) --> \n" RESET_COLOR, pr_token->type);
//         pr_token = pr_token->next;
//     }
//     printf("⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️⚪️\n");
// }

int	tokenization(t_data *data)
{
	if (create_tokens(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (allot_quotes_value(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tokens_insertion(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
