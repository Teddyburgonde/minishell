/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:55:40 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/18 17:34:41 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_redirection_symbol(char *str)
{
	int	count;

	count = 0;
	while (str && (*str == '<' || *str == '>'))
	{
		if (*str == '<' || *str == '>')
			count++;
		str++;
	}
	return (count);
}

static int	get_redirection_type(char **str, t_redirection *redirection)
{
	if (count_redirection_symbol(*str) > 2)
		redirection->redirection_type = UNASIGNED;
	else if (count_redirection_symbol(*str) == 2)
	{
		if (str[0][0] == '<' && str[0][1] == '<')
			redirection->redirection_type = REDIRECTION_HEREDOC;
		else if (str[0][0] == '>' && str[0][1] == '>')
			redirection->redirection_type = REDIRECTION_APPEND;
		else
			redirection->redirection_type = UNASIGNED;
		*str += 2;
	}
	else
	{
		if (str[0][0] == '<')
			redirection->redirection_type = REDIRECTION_INFILE;
		else if (str[0][0] == '>')
			redirection->redirection_type = REDIRECTION_OUTFILE;
		else
			redirection->redirection_type = UNASIGNED;
		*str += 1;
	}
	return (redirection->redirection_type);
}

int    get_redirection(t_command_data *command_data, t_segment *segment, char **remaining_line)
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
}