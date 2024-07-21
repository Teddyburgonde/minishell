/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:14:23 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/21 17:05:44 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_segment *ft_lstnew_segment(void)
{
    t_segment *new_segment;
	
	new_segment = ft_calloc(1, sizeof(t_segment));
    if (!new_segment)
        return NULL;
    new_segment->arguments = NULL;
    new_segment->redirections = NULL;
    new_segment->next = NULL;
    return (new_segment);
}

t_redirection	*ft_lstnew_redirection(char *content, t_redirection_type type)
{
	t_redirection	*new_node;

	new_node = ft_calloc(1, sizeof(t_redirection));
	if (!new_node)
		return (NULL);
	new_node->content_to_expand = content;
    new_node->redirection_type = type;
	new_node->expanded_content = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_argument	*ft_lstnew_argument(char *content)
{
	t_argument	*new_node;

	new_node = ft_calloc(1, sizeof(t_argument));
	if (!new_node)
		return (NULL);
	new_node->content_to_expand = content;
	new_node->expanded_content = NULL;
	new_node->next = NULL;
	return (new_node);
}
