/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:21:43 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/22 18:02:13 by tebandam         ###   ########.fr       */
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

int	manage_redirections_append(t_redirection *redirection)
{
	redirection->fd = open(redirection->expanded_content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirection->fd == -1)
	{
		perror(redirection->expanded_content);
		return (1);
	}
	return (0);
}

int	manage_redirections_infile(t_redirection *redirection)
{
	redirection->fd = open(redirection->expanded_content, O_RDONLY);
	if (redirection->fd == -1)
	{
		perror(redirection->expanded_content);
		return (1);
	}
	return (0);
}

static void	process_heredoc(t_redirection *redirection, int fd, char *content)
{
	while (g_sig != 130)
	{
		content = readline("> ");
		printf("%s\n", content);
		printf("%s\n", redirection->expanded_content);
		if (content == NULL)
		{
			ft_putstr_fd("minishell: warning: end-of-file ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted '", 2);
			ft_putstr_fd(redirection->expanded_content, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strcmp(content, redirection->expanded_content) == 0)
		{
			printf("Je sors\n");
			free(content);
			content = NULL;
			close(fd);
			break ;
		}
		ft_putstr_fd(content, fd);
		ft_putstr_fd("\n", fd);
		free(content);
		content = NULL;
	}
}

void	ft_heredoc(t_command_data *data, t_redirection *redirection)
{
	char	*content;

	redirection->fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->fd == -1)
	{
		perror("heredoc");
		data->exit_code = 1;
		return ;
	}
	content = NULL;
	process_heredoc(redirection, redirection->fd, content);
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
				manage_redirections_outfile(tmp_redirection);
			else if (tmp_redirection->redirection_type == REDIRECTION_INFILE)
				manage_redirections_infile(tmp_redirection);
			else if (tmp_redirection->redirection_type == REDIRECTION_APPEND)
				manage_redirections_append(tmp_redirection);
			else if (tmp_redirection->redirection_type == REDIRECTION_HEREDOC)
				ft_heredoc(command_data, tmp_redirection);
			tmp_redirection = tmp_redirection->next;
		}
		tmp_segment = tmp_segment->next;
	}
	return (0);
}