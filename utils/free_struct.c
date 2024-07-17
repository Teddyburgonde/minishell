/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:02:29 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 20:13:21 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_arguments_struct(t_argument *argument)
{
    t_argument *tmp;
    
    while (argument != NULL) 
    {
        tmp = argument;
        argument = argument->next;
        if (tmp->content_to_expand != NULL)
            free(tmp->content_to_expand);
        free(tmp);
    }
}

void    free_redirections_struct(t_redirection *redirection)
{
    t_redirection *tmp;
    
    while (redirection != NULL)
    {
        tmp = redirection;
        redirection = redirection->next;
        if (tmp->content_to_expand != NULL)
            free(tmp->content_to_expand);
        free(tmp);
    }
}

void    free_segments_struct(t_segment *segment)
{
    t_segment *tmp;

    while (segment != NULL)
    {

        tmp = segment;
        segment = segment->next;
        if (tmp->arguments != NULL)
            free_arguments_struct(tmp->arguments);
        if (tmp->redirections != NULL)
            free_redirections_struct(tmp->redirections);
        free(tmp);
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
