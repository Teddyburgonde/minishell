/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:02:29 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/20 10:56:18 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_arguments_struct(t_argument *argument)
{
	t_argument *tmp;

	tmp = argument;
	
	while (ft_argument_lstsize(argument))
	{
		tmp = argument->next;
		if (argument->content_to_expand != NULL)
			free(argument->content_to_expand);
		free(argument);
		argument = tmp;
	}
}

void    free_redirections_struct(t_redirection *redirection)
{
	t_redirection *tmp;
	
	tmp = redirection;
	while (ft_redirection_lstsize(redirection))
	{
		tmp = redirection->next;
		if (redirection->content_to_expand != NULL)
			free(redirection->content_to_expand);
		free(redirection);
		redirection = tmp;
	}
}

void	free_segments_struct(t_segment *segment)
{
	t_segment *tmp;

	tmp = segment;
	while (ft_segment_lstsize(segment))
	{
		tmp = segment->next;
		if (segment->arguments != NULL)
			free_arguments_struct(segment->arguments);
		if (segment->redirections != NULL)
			free_redirections_struct(segment->redirections);
		free(segment);
		segment = tmp;
	}
}

void    free_command_data_struct(t_command_data *command_data)
{
	if (command_data != NULL)
	{
		if (command_data->segments != NULL)
			free_segments_struct(command_data->segments);
		free(command_data);
	}
}
