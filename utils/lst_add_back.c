/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:22 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 20:26:12 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **head, t_env *new_element)
{
	t_env *tmp;

	if (!new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_element;
}


void	ft_lstadd_back_segment(t_segment **head, t_segment *new_element)
{
	t_segment *tmp;
	if (!new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_element;
}

void	ft_lstadd_back_argument(t_argument **head, t_argument *new_element)
{
	t_argument *tmp;
	if (!new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_element;
}

void	ft_lstadd_back_redirection(t_redirection **head, t_redirection *new_element)
{
	t_redirection *tmp;
	if (!new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	tmp = *head;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_element;
}

