/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 07:05:06 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 08:01:35 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirection   *initialize_redirection(void)
{
    t_redirection   *redirection = ft_calloc(1, sizeof(t_redirection));

    if (redirection == NULL)
        return (NULL);
    return (redirection);
}

t_argument      *initialize_argument(void)
{
    t_argument *argument = ft_calloc(1, sizeof(t_argument));

    if (argument == NULL)
        return (NULL);
    return (argument);
}

t_segment       *initialize_segment(void)
{
    t_segment *segment = ft_calloc(1, sizeof(t_segment));

    if (segment == NULL)
        return (NULL);
    return (segment);
}

t_command_line *initialize_command_line(void)
{
    t_command_line *command_line = ft_calloc(1, sizeof(t_command_line));

    if (command_line == NULL)
        return (NULL);
    return (command_line);
}
