/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:02:29 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 08:41:00 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_arguments(t_argument *argument)
{
    while (argument != NULL) 
    {
        t_argument *tmp;

        tmp = argument;
        argument = argument->next;
        if (tmp->content_to_expand != NULL)
            free(tmp->content_to_expand);
        free(tmp);
    }
}

void    free_redirections(t_redirection *redirection)
{
    while (redirection != NULL)
    {
        t_redirection *tmp;

        tmp = redirection;
        redirection = redirection->next;
        if (tmp->content_to_expand != NULL)
            free(tmp->content_to_expand);
        free(tmp);
    }
}

void    free_segments(t_segment *segment)
{
    while (segment != NULL)
    {
        t_segment *tmp;

        tmp = segment;
        segment = segment->next;
        if (tmp->arguments != NULL)
            free_arguments(tmp->arguments);
        if (tmp->redirections != NULL)
            free_redirections(tmp->redirections);
        free(tmp);
    }
}

void    free_command_line(t_command_line *command_line)
{
    if (command_line != NULL)
    {
        if (command_line->segments != NULL)
            free_segments(command_line->segments);
        free(command_line);
    }
}
