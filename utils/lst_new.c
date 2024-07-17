/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:14:23 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 09:43:26 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// ft_lstnew

// ft_lstdel_one
// ft_lstaddback
// ft_lstlast ( si besoin )
// ft_lstsize 

// t_command_line *ft_lstnew_command_line(void) 
// {
//     t_command_line *new_command_line = malloc(sizeof(t_command_line));
//     if (!new_command_line)
//         return (NULL);
//     new_command_line->segments = NULL;
//     return (new_command_line);
// }

t_segment *ft_lstnew_segment(void)
{
    t_segment *new_segment = malloc(sizeof(t_segment));
    if (!new_segment)
        return NULL;
    new_segment->arguments = NULL;
    new_segment->redirections = NULL;
    new_segment->next = NULL;
    return (new_segment);
}

t_redirection	*ft_lstnew_redirecion(char *content, e_redirection_type type)
{
	t_redirection	*new_node;

	new_node = malloc(sizeof(t_redirection));
	if (!new_node)
		return (NULL);
	new_node->content_to_expand = content;
    new_node->redirection_type = type;
	new_node->next = NULL;
	return (new_node);
}

t_argument	*ft_lstnew_argument(char *content)
{
	t_argument	*new_node;

	new_node = malloc(sizeof(t_argument));
	if (!new_node)
		return (NULL);
	new_node->content_to_expand = content;
	new_node->next = NULL;
	return (new_node);
}
