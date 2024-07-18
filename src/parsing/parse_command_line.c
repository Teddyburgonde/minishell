/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:03 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/18 18:24:17 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void parse_command_line(t_command_data *command_data, char *line)
{
	t_segment   *segment;
	char		*remaining_line;



	remaining_line = skip_whitespace(line);
	while (*remaining_line)
	{
		segment = ft_lstnew_segment();
		ft_lstadd_back_segment(&command_data->segments, segment);
		while (*remaining_line && *remaining_line != '|')
		{
			if (*remaining_line == '<' || *remaining_line == '>')
			{
				if (get_redirection(command_data, segment, &remaining_line) != 0)
				{
					// function all free
					free(remaining_line);
					return ; 
				}
			}
			remaining_line = skip_whitespace(remaining_line);
		}
				
		remaining_line = skip_whitespace(remaining_line);
		ft_native_lst_print(*command_data, 2);
	}
}
