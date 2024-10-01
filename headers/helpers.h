/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkostand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:02 by vkostand          #+#    #+#             */
/*   Updated: 2024/09/17 20:07:17 by vkostand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H


char	**ft_arrdup(char **env);
void    init_data(t_data *data, char **env);
void	*free_array(char **str);

#endif