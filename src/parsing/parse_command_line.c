/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:03 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/19 18:07:29 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int    get_redirection(t_command_data *command_data, t_segment *segment, char **remaining_line)
{
	t_redirection		*new_redirection;

	new_redirection = ft_lstnew_redirection(NULL, UNASIGNED);
	get_redirection_type(remaining_line, new_redirection);
	if (new_redirection->redirection_type == UNASIGNED)
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		free(new_redirection);
		return (1);
	}
	*remaining_line = skip_whitespace(*remaining_line);
	if (*remaining_line && extract_line(remaining_line, &new_redirection->content_to_expand) == 0)
		ft_lstadd_back_redirection(&segment->redirections, new_redirection);
	else
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		free(new_redirection);
		return (1);
	}
	return (0);
} */

int	get_argument(t_command_data *command_data, t_segment *segment, char **remaining_line)
{
	t_argument	*new_argument;

	new_argument = ft_lstnew_argument(NULL);
	if (*remaining_line && extract_line(remaining_line, &new_argument->content_to_expand) == 0)
		ft_lstadd_back_argument(&segment->arguments, new_argument);
	else
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		free(new_argument);
		return (1);
	}
	return (0);
}

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
					return ; 
				}
			}
			else
			{
				if (get_argument(command_data, segment, &remaining_line) != 0)
				{
					// function to free everything
					return ;
				}
			}
			remaining_line = skip_whitespace(remaining_line);
		}
		remaining_line = skip_whitespace(remaining_line);
		ft_native_lst_print(*command_data, 2);
	}
}
