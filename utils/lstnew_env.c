/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:24:17 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 18:26:14 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(void)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
	{
		write (2, "Initialize environment variable has an error.\n", 46);
		return (NULL);
	}
	list->next = NULL;
	return (list);
}
