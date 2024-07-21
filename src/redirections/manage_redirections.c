/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:21:43 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/21 19:36:43 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// t_redirection		*redirections;

int	manage_redirections_outfile(t_redirection *redirection)
{
	redirection->fd = open(redirection->expanded_content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->fd == -1)
	{
		perror(redirection->expanded_content);
		return (1);
	}
	return (0);
}

int	manage_redirections(t_command_data *command_data)
{
	t_segment   *tmp_segment;
	t_redirection *tmp_redirection;

	tmp_segment = command_data->segments;
	
	while (tmp_segment)
	{
		tmp_redirection = tmp_segment->redirections;
		while (tmp_redirection)
		{
			if (tmp_redirection->redirection_type == REDIRECTION_OUTFILE)
				manage_redirections_outfile(t_redirection *redirection);
			else if (tmp_redirection->redirection_type == REDIRECTION_INFILE)
			{
				// function redirection_infile
			}
			else if (tmp_redirection->redirection_type == REDIRECTION_APPEND)
			{
				// function redirection_append 
			}
			else if (tmp_redirection->redirection_type == REDIRECTION_HEREDOC)
			{
				// function redirection_heredoc
			}
		}
		tmp = tmp->next;
	}
}