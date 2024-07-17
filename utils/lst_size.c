/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:18:54 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 14:09:20 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirection_lstsize(t_redirection *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}

int	ft_argument_lstsize(t_argument *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}

int ft_segment_lstsize(t_segment *lst)
{
    int	counter;

	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
