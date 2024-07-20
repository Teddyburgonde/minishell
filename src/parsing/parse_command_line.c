/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:03 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/20 14:25:12 by tebandam         ###   ########.fr       */
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

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '\n')
		return (1);
	return (0);
}

bool	is_pipe_last_char(char **remaining_line)
{
	if (remaining_line[0][0] == '|')
	{
		(*remaining_line)++;
		while (remaining_line[0][0])
		{
			if (ft_isspace(remaining_line[0][0]) == 0)
				return (false);
			(*remaining_line)++;
		}
	}
	else 
		return (false);
	return (true);
}

int parse_command_line(t_command_data *command_data, char *line)
{
	t_segment   *segment;
	char		*remaining_line;

	remaining_line = skip_whitespace(line);
	if (remaining_line[0] == '|')
	{
		ft_putstr_fd("Syntax error\n", 2);
		command_data->exit_code = 2;
		return (1);
	}
	while (*remaining_line)
	{
		segment = ft_lstnew_segment();
		ft_lstadd_back_segment(&command_data->segments, segment);
		while (*remaining_line && *remaining_line != '|')
		{
			if (*remaining_line == '<' || *remaining_line == '>')
			{
				if (get_redirection(command_data, segment, &remaining_line) != 0)
					return (1); 
			}
			else
			{
				if (get_argument(command_data, segment, &remaining_line) != 0)
					return (1);
			}
			remaining_line = skip_whitespace(remaining_line);
		}
		if (is_pipe_last_char(&remaining_line) == true)
		{
			ft_putstr_fd("Syntax error\n", 2);
			command_data->exit_code = 2;
			return (1);
		}
		remaining_line = skip_whitespace(remaining_line);
	}
	return (0);
}
